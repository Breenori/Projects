# Author: Sebastian Pritz

import re

'''
das ist ein MehrzeilenKommentar
'''

geneFile = open("imgtSpeciesGeneInformation.txt")

# Define a boolean to skip the first line.
firstLine = True
geneDict = dict()

# Loop through all lines in the file
for line in geneFile.readlines():
    if firstLine:
        firstLine = False
    else:
        # Determine species and genedefinition
        species = line.split(';')[0]
        geneName = line.split(';')[1][3]

        # If species not in dictionary, add a new dictionary entry.
        if species not in geneDict.keys():
            geneDict[species] = dict()
            geneDict[species]['V']=0
            geneDict[species]['D']=0
            geneDict[species]['J']=0

        # If species present, just increase existing entries
        if geneName in ['V', 'D', 'J']:
            geneDict[species][geneName] += 1

# Print a formatted table header.
print("{:<30}".format("Species"), "{:<15}".format("V-Count"), "{:<15}".format("D-Count"), "{:<15}".format("J-Count"))

# Print the formatted table body
for species in geneDict:
    print("{:<30}".format(species), "{:<15}".format(geneDict[species]['V']), "{:<15}".format(geneDict[species]['D']), "{:<15}".format(geneDict[species]['J']))
        

        