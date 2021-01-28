# Übungsabgabe 02
# Sebastian Pritz
# Python Version 3.9.0
# Stundenaufwand: 5h

import re

def printStatistics(filename):
    geneFile = open(filename)

    # Define a boolean to skip the first line.
    firstLine = True
    geneDict = dict()

    # Loop through all lines in the file
    for line in geneFile.readlines():
        if firstLine:
            firstLine = False
        else:
            # Determine species and genesegment
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

    geneFile.close()

    


    outputFile = open("statistics.txt", 'w')

    # Print a formatted table header.
    outputFile.write("{:<30}".format("Species") + "{:<15}".format("V-Count") + "{:<15}".format("D-Count") + "{:<15}".format("J-Count") + "\n")

    # Print the formatted table body
    for species in geneDict:
        outputFile.write("{:<30}".format(species) + "{:<15}".format(geneDict[species]['V']) + "{:<15}".format(geneDict[species]['D']) + "{:<15}".format(geneDict[species]['J']) + "\n")
    outputFile.close()
    
printStatistics("imgtSpeciesGeneInformation.txt")

        