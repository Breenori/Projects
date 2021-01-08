# HelloWorldFoundOnLineOne
# = HWFOO
# SKS3 - Sebastian Pritz und Severin Pichler

# Kommentare
from fuzzywuzzy import fuzz
from fuzzywuzzy import process
import re

print ("''' Seas oida wos geht'''")

'''
seas severin
was machst
'''

var = "test" '''this is treachery'''

def isInsideString(string, pos):
    dqts = 0
    sqts = 0
    lastFound = ''
    if pos == 0 or pos == len(string)-1:
        return False
    elif pos > len(string)/2:
        while pos < len(string)-1:
            pos += 1
            if string[pos]=='"':
                dqts += 1
                lastFound = '"'
            elif string[pos]=='\'':
                sqts += 1
                lastFound = '\''
           
    elif pos <= len(string)/2:
        while pos > 0:
            pos -= 1
            if string[pos]=='"':
                dqts += 1
                lastFound = '"'
            elif string[pos]=='\'':
                sqts += 1
                lastFound = '\''


    if lastFound == '':
        return False;
    elif lastFound == '"':
        return dqts%2==1
    elif lastFound == '\'':
        return sqts%2==1



def preprocess(fileHandle):
    insideBlockComment = False
    blockComment = "'''"
    lines = list()
    
    for line in fileHandle.readlines():
        wasComment = False
        # Strip the line of all strings and interruptive special characters (like \n)
        line = line.lower()
        line = re.sub('\n','',line)

        # If line is inside a block comment, a block end has to be found. Ignore everything else.
        if insideBlockComment:
            blockEndPos = line.find(blockComment)
            # If it has been found, reset comment state and remove commented part.
            if blockEndPos != -1:
                line = line[blockEndPos+len(blockComment):]
                insideBlockComment = False
                expectedBlockEnd = ""
        else:
            # Remove all line comments and code thats commented out.
            commentPos = line.find('#')
            # Also make sure that the # is not inside a string.
            if commentPos != -1 and not isInsideString(line, commentPos):
                line = line[0:commentPos]
                wasComment = True

            # Some programming languages support inline blockcomments between code.
            # Following 2 lines remove all blockcomments that are started AND ended in the same line.
            # Use negative lookahead regex to avoid removing code between blockcomments.
            blockSearch = re.escape(blockComment)+"((?!"+re.escape(blockComment)+").)*"+re.escape(blockComment)+"(?!\")"
            line = re.sub(blockSearch, '', line)
            
            # If there is only a single blockComment inside a line, enter insideBlockComment state and remove the commented part
            blockBeginPos = line.find("'''")
            if blockBeginPos != -1 and not isInsideString(line, blockBeginPos):
                line = line[0:blockBeginPos]
                insideBlockComment = True
                wasComment = True

            # If there is something left in the line, append it to the list
            if not wasComment:
                lines.append(line)

    return lines


'''
dude 
what the henk
'''

referenceFile = open("HWFOO.py", 'r')
#candidateFile = open("candidateFile.txt")

lineList = preprocess(referenceFile)

for line in lineList:
    print(line)





