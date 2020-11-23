# Übungsabgabe 02
# Sebastian Pritz
# Python Version 3.9.0
# Stundenaufwand: 5h

import re

aaFile = open("aa.txt", 'r')

aaDict = dict()

# Loop through the file line by line
for line in aaFile.readlines():
    line = line.strip()
    elements = line.split()
    name = elements[0]

    # Use the splitted line to get the name, 1 digit code, 3 digit code and the acyl group
    if name not in aaDict.keys():
        aaDict[name] = list()
    aaDict[name].append(elements[1])
    aaDict[name].append(elements[3])
    aaDict[name].append(elements[2])
aaFile.close()

# After getting the data from the aa file, read isoelectric point data from other file
isoFile = open("iso.txt", 'r')
for line in isoFile.readlines():
    line = line.strip()
    elements = line.split()
    name = elements[0]

    # Add the isoelectric point as a floating point number to the list.
    if name not in aaDict.keys():
        aaDict[name] = list()
    aaDict[name].append(float(elements[3].replace(',','.')))
isoFile.close()

# last but not least, output the dictionary and its values.
for aa in aaDict.keys():
    print("{:<15}".format(aa),"\t",aaDict[aa][0],"\t","{:<15}".format(aaDict[aa][1]),"\t",aaDict[aa][2],"\t",aaDict[aa][3])


