import re
import os

file = open('1_Summary_B3006TRBA.txt')

vfile = open('V_genes.txt','w')
dfile = open('D_genes.txt','w')
jfile = open('J_genes.txt','w')

V_genes = dict()
D_genes = dict()
J_genes = dict()

for line in file.readlines():
    match = re.findall('(TRB[VDJ][^*]*)',line)
    print(line)

    for entry in match:
        if entry[3]=='V':
            if entry not in V_genes.keys():
                V_genes[entry]=0
            V_genes[entry]=+1
        elif entry[3]=='D':
            if entry not in D_genes.keys():
                D_genes[entry]=0
            D_genes[entry]=+1
        elif entry[3]=='J':
            if entry not in J_genes.keys():
                J_genes[entry]=0
            J_genes[entry]=+1

sorted(J_genes)
sorted(D_genes)
sorted(V_genes)

print(J_genes)

vfile.write('Gen\tAnzahl\n')
for entry in V_genes.keys():
    vfile.write(entry+'\t\t'+str(V_genes[entry])+'\n')

vfile.close()
dfile.close()
jfile.close()
