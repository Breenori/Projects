# Übungsabgabe 02
# Sebastian Pritz
# Python Version 3.9.0
# Stundenaufwand: 5h

import re

pythonFile = open("TestScript.py", 'r')
#pythonFile = open("MergeSort.cpp", 'r')

# Define line comments from several languages
lineCommentTypes = set()
lineCommentTypes.add("#")
lineCommentTypes.add("//")
lineCommentTypes.add("--")

# Define block comments from several languages
blockCommentStart = set()
blockCommentEnd = dict()

blockCommentStart.add("'''")
blockCommentEnd["'''"]="'''"

blockCommentStart.add("<!--")
blockCommentEnd["<!--"]="-->"

blockCommentStart.add("/*")
blockCommentEnd["/*"]="*/"

# Variables to keep track of comment state
insideBlockComment = False
expectedBlockEnd = ""


# Create a dictionary to store all the crossreferences
commandDict = dict()


# Loop through all the lines
lineNumber = 0
for line in pythonFile:
    lineNumber += 1

    # Strip the line of all strings and interruptive special characters (like \n)
    line = line.strip().lower()
    line = re.sub('\"[^\"]*\"', '', line)
    line = re.sub('\'[^\']\'', '', line)

    # If line is inside a block comment, a block end has to be found. Ignore everything else.
    if insideBlockComment:
        blockEndPos = line.find(expectedBlockEnd)
        # If it has been found, reset comment state and remove commented part.
        if blockEndPos != -1:
            line = line[blockEndPos+len(expectedBlockEnd):]
            insideBlockComment = False
            expectedBlockEnd = ""
    
    # If current line
    if not insideBlockComment:
        # Remove all line comments and code thats commented out.
        for commentType in lineCommentTypes:
            commentPos = line.find(commentType)
            if commentPos != -1:
                line = line[0:commentPos]

        # Handle all block comments
        for blockType in blockCommentStart:
            # Some programming languages support inline blockcomments between code.
            # Following 2 lines remove all blockcomments that are started AND ended in the same line.
            # Use negative lookahead regex to avoid removing code between blockcomments.
            blockSearch = re.escape(blockType)+"((?!"+re.escape(blockCommentEnd[blockType])+").)*"+re.escape(blockCommentEnd[blockType])
            line = re.sub(blockSearch, '', line)
            
            # If there is a single block comment start remaining, remove the commented part and update comment state.
            blockBeginPos = line.find(blockType)
            if blockBeginPos != -1:
                line = line[0:blockBeginPos]
                insideBlockComment = True
                expectedBlockEnd = blockCommentEnd[blockType]

        # After dealing with all comments, remove the remaining interfering characters
        line = re.sub('[\=\+\-\*\/\<\>&\|\:\,\;\~\?\%\$\!]', ' ', line)
        line = re.sub('[\(\)]', ' ', line)
        line = re.sub('[\[\]]', ' ', line)
        line = re.sub('[\{\}]', ' ', line)
        line = re.sub('\.', ' ', line)
        line = re.sub('\s[0-9]\s?', ' ', line)
        line = re.sub(' +', ' ', line)

        # This leaves only variables and functionnames.
        # If there is something left in the line, save each word and linenumber to the dictionary.
        if len(line) > 0:
            for command in line.split(' '):
                if len(command)>0:
                    if command not in commandDict.keys():
                        commandDict[command] = set()
                    commandDict[command].add(lineNumber)

# Output the results
for command in sorted(commandDict.keys()):
    lineNumberString = ""
    for lineNumber in sorted(commandDict[command]):
        lineNumberString += str(lineNumber) + ", "
    lineNumberString = lineNumberString[:-2]
    print("{:<20}".format(command),lineNumberString)