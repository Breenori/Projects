# Uebungsabgabe 01
# Sebastian Pritz
# Python Version 3.9.0
# Stundenaufwand: 2h

def printStatistics(countA, countC, countG, countT):
    total = countA+countC+countG+countT
    if total>0:
        print("Sequenz ",cursequence, "Gesamtlänge der Sequenz", total)
        print("A: ",round(countA/total,2)," (", countA,"/",total,")")
        print("C: ",round(countC/total,2)," (", countC,"/",total,")")
        print("G: ",round(countG/total,2)," (", countG,"/",total,")")
        print("T: ",round(countT/total,2)," (", countT,"/",total,")",'\n')

fastaFile = open('Daten/E coli.fasta','r')
cursequence = 0
charcount = 0

for line in fastaFile.readlines():
    if line[0] == '>':
        if cursequence > 0:
            printStatistics(countA, countC, countG, countT)
        cursequence += 1
        countA = 0
        countC = 0
        countG = 0
        countT = 0
    else:
        for char in line:
            if char == 'A':
                countA += 1
            elif char == 'C':
                countC += 1
            elif char == 'G':
                countG += 1
            elif char == 'T':
                countT +=1

printStatistics(countA, countC, countG, countT)


        
