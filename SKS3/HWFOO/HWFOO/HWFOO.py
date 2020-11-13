# HelloWorldFoundOnLineOne
# = HWFOO
# SKS3 - Sebastian Pritz und Severin Pichler

# Kommentare
from fuzzywuzzy import fuzz
from fuzzywuzzy import process


def preprocess(fileHandle, outputName):
    outputFile = open(outputName, 'w')

    isBlockComment = False
    
    for line in fileHandle.readlines():
        line = line.strip()

        # if line = blockcomment begin

        boolol = (len(line) > 0) and (line[0]!='#') and not isBlockComment

        if boolol:
            outputFile.write(line+"\n")

    outputFile.close()  # hier wird da streamsi zuagmocht oida


'''
dude 
what the henk
'''

referenceFile = open("HWFOO.py", 'r')
#candidateFile = open("candidateFile.txt")

preprocess(referenceFile, "hannes.txt")



