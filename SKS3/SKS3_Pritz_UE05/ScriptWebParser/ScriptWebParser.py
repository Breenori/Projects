# Übungsabgabe 05
# Sebastian Pritz
# Python Version 3.7.2
# Stundenaufwand: 4h

import urllib.request
import re
import sqlite3

def parseBonusInfo(url):
    # Get the website
    html = urllib.request.urlopen(r'https://de.wikipedia.org/'+url)

    # Define the fields we want.
    interestingFields = {"Paradigmen:","Erscheinungsjahr:","Betriebssystem:","Entwickler:"}
   
    # create an empty list to hold all the values we want.
    bonus = list()

    # define regular expressions
    startRex = re.compile('^.*<table.*infobox.*>')
    endRex = re.compile('^.*<\/table>')
    headerRex = re.compile('<td><b>(<[^<>]*>)*(.*)')
    contentRex = re.compile('^<td>(<[^<>]*>)*(.*)')

    # Read the html file line by line and decode it (bytearray...)
    line = html.readline().decode('utf-8')

    # First, search the start of the box
    while not startRex.match(line) and line != '':
        line = html.readline().decode('utf-8')
    
        # If it's been found, search for the respective headers and get their content
    found = False
    while not endRex.match(line) and line != '':
        # If a header has been found previously and it is part of the interestingFields, search for its content
        if found and stripHtml((found.group(2))) in interestingFields:
            match = contentRex.match(line)
            if match:
                bonus.append(stripHtml((found.group(2))) + " " + stripHtml(match.group(2).strip()))
                found = False
        # If no header has been found, search for a header
        else:
            found = headerRex.match(line)

        line = html.readline().decode('utf-8')

    return bonus

def stripHtml(string):
    # Substitute all remaining html-tags
    newString = re.sub('<[^<>]*>|<\/[^<>]*>','',string)
    # ... and also all remaining html entities that failed to decode
    newString = re.sub('&[^;]*;[0-9]*','',newString)
    return newString

def parseScriptingLanguages():
    # Get the page
    html = urllib.request.urlopen(r'https://de.wikipedia.org/wiki/Skriptsprache')

    # Create dict with all necessary categories
    entries = dict()
    entries["Skriptsprachen, die als Bibliothek verfügbar sind"] = list()
    entries["Skriptsprachen verschiedener Programme"] = list()
    entries["Skriptsprachen im WWW"] = list()

    # Regular expressions to find table beginnings as well as list entries (script languages)
    titleRex = re.compile('^<h3>[^<>]*<span.* class="mw-headline"[^<>]*>([^<>]*)<\/span>')
    listRex = re.compile('^(<ul>)?<li><a[^<>]* href=\"([^\"]*)\"[^<>]*>([^<>]*)<\/a>(.*)<\/li>')

    # Variables to hold which category we are currently parsing
    titleFound = False
    curTitle = ""

    # Go through all lines
    for line in html.readlines():
        # decode the bytearray
        line = line.decode('utf-8')

        # search for table with the right category
        titleMatch = titleRex.match(line)

        if titleMatch:
            # if it matches and it has the right category, set the variables accordingly
            if titleMatch.group(1) in entries.keys():
                titleFound = True
                curTitle = titleMatch.group(1)
            # else, unset them.
            else:
                titleFound = False
        
        # If a title has been found, check all of the tables list entries
        if titleFound:
            listMatch = listRex.match(line)
            if listMatch:
                tmp = list()
                tmp.append(listMatch.group(3)) # Scriptlanguage name
                tmp.append(stripHtml(listMatch.group(4)))   # Script language basic info
                tmp.append(parseBonusInfo(listMatch.group(2)))  # script language bonus info (parse the url)
                entries[curTitle].append(tmp)

    return entries
 

# get all the entries
entries = parseScriptingLanguages()

# initialize db connection
conn = sqlite3.connect('../SKS3_Pritz_UE05/db.sqlite3')
cur = conn.cursor()

type_id = 1
lang_id = 1

# reset the sequences to start from 0
cur.execute("delete from SKSApp_scriptlangs")
cur.execute("delete from SKSApp_scriptlangsadd")
cur.execute("delete from sqlite_sequence where name='SKSApp_scriptlangs'")
cur.execute("delete from sqlite_sequence where name='SKSApp_scriptlangsadd'")
# go through all categories/types
for type in entries.keys():
    category = entries[type]
    # Insert all languages
    for entry in category:
        print('INSERT INTO SKSApp_scriptlangs(name,desc,type_id) values("'+entry[0]+'", "'+entry[1]+'",'+str(type_id)+')')
        cur.execute('INSERT INTO SKSApp_scriptlangs(name,desc,type_id) values("'+entry[0]+'", "'+entry[1]+'",'+str(type_id)+')')
        # and also insert all bonus info for languages
        for subentry in entry[2]:
            print('\tINSERT INTO SKSApp_scriptlangsadd(field,info,lang_id) values("'+str(subentry).split(':')[0].strip()+'","'+str(subentry).split(':')[1].strip()+'",'+str(lang_id)+')')
            cur.execute('INSERT INTO SKSApp_scriptlangsadd(field,info,lang_id) values("'+str(subentry).split(':')[0].strip()+'","'+str(subentry).split(':')[1].strip()+'",'+str(lang_id)+')')
        lang_id+=1
    type_id+=1

conn.commit()
conn.close()