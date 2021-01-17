import urllib.request
import re
import sqlite3

def parseBonusInfo(url):
    html = urllib.request.urlopen(r'https://de.wikipedia.org/'+url)
    interestingFields = set()
    interestingFields.add("Paradigmen:")
    interestingFields.add("Erscheinungsjahr:")
    interestingFields.add("Betriebssystem:")
    interestingFields.add("Entwickler:")
    bonus = list()

    startRex = re.compile('^.*<table.*infobox.*>')
    endRex = re.compile('^.*<\/table>')
    headerRex = re.compile('<td><b>(<[^<>]*>)*(.*)')
    contentRex = re.compile('^<td>(<[^<>]*>)*(.*)')

    line = html.readline().decode('utf-8')
    while not startRex.match(line) and line != '':
        line = html.readline().decode('utf-8')
    
    found = False
    while not endRex.match(line) and line != '':
        if found and stripHtml((found.group(2))) in interestingFields:
            match = contentRex.match(line)
            if match:
                bonus.append(stripHtml((found.group(2))) + " " + stripHtml(match.group(2).strip()))
                found = False
        else:
            found = headerRex.match(line)

        line = html.readline().decode('utf-8')

    return bonus

def stripHtml(string):
    newString = re.sub('<[^<>]*>|<\/[^<>]*>','',string)
    return newString


html = urllib.request.urlopen(r'https://de.wikipedia.org/wiki/Skriptsprache')
entries = dict()
entries["Skriptsprachen, die als Bibliothek verfügbar sind"] = list()
entries["Skriptsprachen verschiedener Programme"] = list()
entries["Skriptsprachen im WWW"] = list()

titleFound = False
curTitle = ""
titleRex = re.compile('^<h3>[^<>]*<span.* class="mw-headline"[^<>]*>([^<>]*)<\/span>')
listRex = re.compile('^(<ul>)?<li><a[^<>]* href=\"([^\"]*)\"[^<>]*>([^<>]*)<\/a>(.*)<\/li>')

for line in html.readlines():
    line = line.decode('utf-8')
    

    titleMatch = titleRex.match(line)

    if titleMatch:
        if titleMatch.group(1) in entries.keys():
            titleFound = True
            curTitle = titleMatch.group(1)
        else:
            titleFound = False

    if titleFound:
        listMatch = listRex.match(line)
        if listMatch:
            tmp = list()
            tmp.append(listMatch.group(3))
            tmp.append(stripHtml(listMatch.group(4)))
            tmp.append(parseBonusInfo(listMatch.group(2)))
            entries[curTitle].append(tmp)
 
            
conn = sqlite3.connect('../SKS3_Pritz_UE05/db.sqlite3')
cur = conn.cursor()

type_id = 1
lang_id = 1
for type in entries.keys():
    category = entries[type]
    for entry in category:
        print('INSERT INTO SKSApp_scriptlangs(name,desc,type_id) values("'+entry[0]+'", "'+entry[1]+'",'+str(type_id)+')')
        cur.execute('INSERT INTO SKSApp_scriptlangs(name,desc,type_id) values("'+entry[0]+'", "'+entry[1]+'",'+str(type_id)+')')
        for subentry in entry[2]:
            print('\tINSERT INTO SKSApp_scriptlangsadd(info,lang_id) values("'+str(subentry)+'",'+str(lang_id)+')')
            cur.execute('\tINSERT INTO SKSApp_scriptlangsadd(info,lang_id) values("'+str(subentry)+'",'+str(lang_id)+')')
        lang_id+=1
    type_id+=1

conn.commit()
conn.close()