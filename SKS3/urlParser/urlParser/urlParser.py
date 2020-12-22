import urllib.request
import re
import os


def writeTxtFiles(downloadList, codex):
    path = os.getcwd() + "\current"
    if not os.path.exists(path) : os.makedirs(path)
    f = open(path + "\\" + str(codex) + ".txt", "w")
    for i in downloadList:
        f.writelines(i+"\n")
    f.close()

geneList = ['IGHV','IGHD','IGHJ']

def loadAntibodyFiles(geneList):
    for i in geneList:
        f = urllib.request.urlopen(r"http://imgt.org/IMGTrepertoire/index.php?section=LocusGenes&repertoire=genetable&species=human&group="+str(i))
        
        listOfGenes=[]
        listOfAlleles=[]

        geneReg = re.compile('<.*class=\"gene_note\".*><.*>(.*)<.*><.*>')
        alleleReg = re.compile('<.*class=\"allele_note\".*><.*>(.*)<.*><.*>')

        for j in f.readlines():
            moGene = re.search(geneReg, str(j));
            moAllele = re.search(alleleReg, str(j));
            if moGene != None:
                listOfGenes.append(moGene.group(1))
            if moAllele != None:
                listOfAlleles.append(moAllele.group(1))
        writeTxtFiles(listOfGenes, i)
        writeTxtFiles(listOfAlleles, i + "Allele")

    return listOfGenes, listOfAlleles

listOfGenes, listOfAlleles = loadAntibodyFiles(geneList)

print(listOfGenes)
print(listOfAlleles)