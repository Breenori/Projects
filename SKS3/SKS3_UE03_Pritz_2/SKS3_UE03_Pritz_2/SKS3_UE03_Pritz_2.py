import urllib.request
import re

def printTree(baseUrl, url, letter, indent, siteSet):
    indentstr = ""
    for i in range(0,indent):
        indentstr += '\t'

    f = urllib.request.urlopen(r""+baseUrl+url)
    reSub = re.compile('<a href="('+letter+'.*html)" title="(.*)".*>')

    for line in f.readlines():
        line = line.decode('utf8').strip()

        tdoPos = 0
        tdcPos = 0
        found = False
        while line.find('<a',tdoPos)>=0 and line.find('</a>',tdcPos)>=0 and not found:
            tdoPos = line.find('<a',tdoPos)
            tdcPos = line.find('</a>',tdoPos)
            
            subMatcher = reSub.match(line[tdoPos:tdcPos])
            if subMatcher and subMatcher.group(1) not in siteSet:
                print(indentstr + re.sub('.html','',subMatcher.group(1)) + '\t' + subMatcher.group(2))
                siteSet.add(subMatcher.group(1))
                if url != subMatcher.group(1):
                    printTree(baseUrl, subMatcher.group(1), url[0], indent+1, siteSet)

            tdoPos += 1
            tdcPos += 1



baseUrl = 'https://www.icd-code.de/icd/code/'
f = urllib.request.urlopen(r"https://www.icd-code.de/icd/code/ICD-10-GM.html")


reEye = re.compile('<td>(.*Auge.*)<a href="(.*html)" ')
reRes = re.compile('<td>(.*Atmungssystem.*)<a href="(.*html)"')

for line in f.readlines():
    line = line.decode('utf8')
    
    tdoPos = 0
    tdcPos = 0
    while line.find('<td',tdoPos)>=0 and line.find('</td>',tdcPos)>=0:
        tdoPos = line.find('<td',tdoPos)
        tdcPos = line.find('</td>',tdcPos)
        
        eyeMatcher = reEye.match(line[tdoPos:tdcPos])
        resMatcher = reRes.match(line[tdoPos:tdcPos])
        if(eyeMatcher):
            print(eyeMatcher.group(2).split('.')[0] + '\t' + eyeMatcher.group(1))
            siteSet = set()
            printTree(baseUrl, eyeMatcher.group(2), eyeMatcher.group(2)[0], 1, siteSet)
        elif(resMatcher):
            print(resMatcher.group(2).split('.')[0] + '\t' + resMatcher.group(1))
            siteSet = set()
            printTree(baseUrl, resMatcher.group(2), resMatcher.group(2)[0], 1, siteSet)

        tdoPos += 1
        tdcPos += 1

