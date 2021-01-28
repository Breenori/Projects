# Übungsabgabe 03
# Sebastian Pritz
# Python Version 3.7.0
# Stundenaufwand: 8h
import urllib.request
import re

# Recursive function to iterate through all links.
def printTree(baseUrl, url, letter, indent, siteSet):
    # Calculate indentation for tree-look
    indentstr = ""
    for i in range(0,indent):
        indentstr += '\t'

    f = urllib.request.urlopen(r""+baseUrl+url)
    # Regular expression to find the name of the object and the link to its site
    reSub = re.compile('<a href="('+letter+'.*html)" title="(.*)".*>')

    # Go through all lines
    for line in f.readlines():
        # Convert binary to string by decoding.
        line = line.decode('utf8').strip()

        # variables to safe state
        tdoPos = 0
        tdcPos = 0
        found = False
        # Find all <a> tags, but only evaluate first one. (tags are stated twice on icd)
        while line.find('<a',tdoPos)>=0 and line.find('</a>',tdcPos)>=0 and not found:
            tdoPos = line.find('<a',tdoPos)
            tdcPos = line.find('</a>',tdoPos)
            
            # Match the <a> Tag for information
            subMatcher = reSub.match(line[tdoPos:tdcPos])
            if subMatcher and subMatcher.group(1) not in siteSet:
                # Print tree and continue iteration.
                print(indentstr + re.sub('.html','',subMatcher.group(1)) + '\t' + subMatcher.group(2))
                siteSet.add(subMatcher.group(1))
                if url != subMatcher.group(1):
                    printTree(baseUrl, subMatcher.group(1), url[0], indent+1, siteSet)

            tdoPos += 1
            tdcPos += 1



baseUrl = 'https://www.icd-code.de/icd/code/'
f = urllib.request.urlopen(r"https://www.icd-code.de/icd/code/ICD-10-GM.html")

# Regex for main site
reEye = re.compile('<td>(.*Auge.*)<a href="(.*html)" ')
reRes = re.compile('<td>(.*Atmungssystem.*)<a href="(.*html)"')


# Same as above function, but for the main site. Slightly altered.
for line in f.readlines():
    line = line.decode('utf8')
    
    tdoPos = 0
    tdcPos = 0
    while line.find('<td',tdoPos)>=0 and line.find('</td>',tdcPos)>=0:
        tdoPos = line.find('<td',tdoPos)
        tdcPos = line.find('</td>',tdcPos)
        
        # Regex to find lines for eye and respiratory system diseases
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

