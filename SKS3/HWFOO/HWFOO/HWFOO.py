# HelloWorldFoundOnLineOne
# = HWFOO
# SKS3 - Sebastian Pritz und Severin Pichler

# Kommentare
from fuzzywuzzy import fuzz
from fuzzywuzzy import process

def isInsideString(string, pos):
    dqts = 0
    sqts = 0
    lastFound = ' '
    if pos > len(string)/2:
        while pos < len(string):
            if string[pos]=='"':
                dqts += 1
                lastFound = '"'
            elif string[pos]=='\'':
                sqts += 1
                lastFound = '\''

    if lastFound == ' ':
        return true;
    elif lastFound == '"':
        return dqts%2==0
    elif lastFound == '\'':
        return sqts%2==0



def preprocess(fileHandle):
    isBlockString = False
    isBlockComment = False
    lines = list()
    
    for line in fileHandle.readlines():

        # Strip the line of all strings and interruptive special characters (like \n)
        line = line.strip().lower()

        # If line is inside a block comment, a block end has to be found. Ignore everything else.
        if insideBlockComment:
            blockEndPos = line.find("'''")
            # If it has been found, reset comment state and remove commented part.
            if blockEndPos != -1:
                line = line[blockEndPos+len("'''"):]
                insideBlockComment = False
                expectedBlockEnd = ""

         # If current line
        if not insideBlockComment:
            # Remove all line comments and code thats commented out.

            commentPos = line.find('#')
            if commentPos != -1 and not isInsideString(commentPos):
                line = line[0:commentPos]

            # Some programming languages support inline blockcomments between code.
            # Following 2 lines remove all blockcomments that are started AND ended in the same line.
            # Use negative lookahead regex to avoid removing code between blockcomments.
            blockSearch = re.escape(blockType)+"((?!"+re.escape(blockCommentEnd[blockType])+").)*"+re.escape(blockCommentEnd[blockType])
            line = re.sub(blockSearch, '', line)
            
            # If there is a single block comment start remaining, remove the commented part and update comment state.
            blockBeginPos = line.find("'''")
            if blockBeginPos != -1:
                line = line[0:blockBeginPos]
                insideBlockComment = True
                expectedBlockEnd = "'''"

            # If there is something left in the line, append it to the list
            if len(line) > 0:
                lines.append(line)


'''
dude 
what the henk
'''

referenceFile = open("HWFOO.py", 'r')
#candidateFile = open("candidateFile.txt")

lineList = preprocess(referenceFile)



