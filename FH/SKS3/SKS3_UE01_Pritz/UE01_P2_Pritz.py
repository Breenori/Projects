# Uebungsabgabe 01
# Sebastian Pritz
# Python Version 3.9.0
# Stundenaufwand: 2h

# Returns complementary DNA for a given sequence
def getComplementary(sequence):
    stringList = list(sequence)

    for i in range(0, len(sequence)):
        if sequence[i] == 'A':
            stringList[i] = 'T'
        elif sequence[i] == 'T':
            stringList[i] = 'A'
        elif sequence[i] == 'C':
            stringList[i] = 'G'
        elif sequence[i] == 'G':
            stringList[i] = 'C'
    return "".join(stringList)

# Prints a given list of FASTA sequences
def printSequences(seqList):
    # Keep track of number of sequences
    seqNr = 1
    for curList in seqList:
        print("Sequenz:",seqNr)
        print("DNA Sequenz\t\t\tReverse Sequenz\t\t\tKomplementäre Sequenz\t\tR. k. Sequenz")
        seqNr += 1

        # Since reversing each line isn't enough, we also reverse the entire list.
        # This ensures proper reversal.
        revList = curList[::-1]

        # Print each line of the current list
        for lineIndex in range(0, len(curList)):
            # Get normal and calculate complementary from curList
            line = curList[lineIndex]
            compString = getComplementary(line)

            # Calculate the reversed and complementary reversed sequences
            revLine = revList[lineIndex]
            reverseCompString = getComplementary(revLine)[::-1]
            reverseString = revLine[::-1]

            print('',line,'\t', reverseString,'\t', compString,'\t',reverseCompString)
        print('\n')


# Taking data from an altered, tiny version of the e coli fasta file.
# Creating the file handler.
fastaFile = open('Daten/E coli mini.fasta','r')

# Create new lists to store the data which is being read from the file
sequenceList = list()
lineList = list()

seqNr = 0

# Read each line of the file
for line in fastaFile.readlines():
    # If line is sequence header (>), empty the list and increase sequence counter
    if line[0] == '>':
        if seqNr > 0:
            sequenceList.append(lineList)
        lineList = list()
        seqNr += 1
    # If line isn't a header and not empty, remove \n and add it to the line list.
    elif len(line)>1:
        lineList.append(line.strip('\n'))
fastaFile.close()

# If non empty lines have been read in, add the line list to the sequence list.
if len(lineList)>0:
    sequenceList.append(lineList)

printSequences(sequenceList)

    
