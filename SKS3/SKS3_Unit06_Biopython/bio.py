from Bio.Seq import Seq, transcribe, back_transcribe, translate, MutableSeq

#GC Gehalt
from Bio.SeqUtils import GC

from Bio import SeqIO
from Bio import Entrez
Entrez.email = 'a@b.at'
from Bio.PDB import *

mySequence = Seq("ACGTACGT")
mySecondSequence = Seq("ACGTACCGTG")

print(mySequence)

print(mySequence[0])
stringSequence = str(mySecondSequence)

format_fast_string = ">Genname\n%s\n" % mySecondSequence
print(format_fast_string)

# Zusammenfügen bzw. Konkatenieren von Sequenzen
# ACHTUNG BEIM ARBEITEN von unterschiedlichen Seqs Typ check
dna_seq = Seq("ACGTA")
protein_seq = Seq("EVRNAK")

print ("Sum: ", protein_seq + dna_seq)
print(dna_seq)
print(dna_seq.complement())
print(dna_seq.reverse_complement())

# Transcription and Tanslation
coding_dna = Seq("ATGGCCATTGTAATG")
template_dna = coding_dna.reverse_complement()
messenger_rna = transcribe(coding_dna)
print(messenger_rna)

print(back_transcribe(messenger_rna))
print(translate(messenger_rna))

myThirdSequence = Seq("GATCGATGGGGGCTATCC")
print(GC(myThirdSequence))

# MutableSeq objects
print(dna_seq)
#dna_seq[0]="T" --> Nicht veränderbar!
mutable_seq = dna_seq.tomutable()
mutable_seq[0] = "T"
print(mutable_seq)

mutableSeq = MutableSeq("GCCCATC")
mutableSeq[1] = "A"
print(mutableSeq)
print('\n')

#----------------------------------------

print("FASTA File")
handle = open("ecoli.fasta")

for seq_record in SeqIO.parse(handle, 'fasta'):
    print(seq_record.id)
    print(len(seq_record.seq))
    print(repr(seq_record.seq))
handle.close()

print("Clustal W Files")
handle = open("clustalw.clustal_num")
for seq_record in SeqIO.parse(handle, "clustal"):
    print(seq_record.id)
handle.close()

#--------------------------------------
print("Entrez information")
handle = Entrez.einfo()
result = handle.read()
print(result)

handle = Entrez.efetch(db="nucleotide", id="57240072", rettype="gb", retmode="text")
for i in handle.readlines():
    print(i.strip())
print(handle.readline().strip())
handle.close()

#-----------

print("PDB Files")

pdb1 = PDBList()
pdbFile = pdb1.retrieve_pdb_file('1FAT')
print(pdbFile)

handle = open("pdb1fat.ent", 'r')
header_dict = parse_pdb_header(handle)
print(header_dict)


p = PDBParser()
structure = p.get_structure('X', 'pdb1fat.ent')
for model in structure:
    for chain in model:
        print(chain)
        for residue in chain:
            print(residue)
            for atom in residue:
                print(atom)
                break

for atom in structure.get_atoms():
    print(atom)

