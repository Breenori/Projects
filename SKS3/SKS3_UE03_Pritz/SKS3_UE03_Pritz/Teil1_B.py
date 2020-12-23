# Übungsabgabe 03
# Sebastian Pritz
# Python Version 3.7.0
# Stundenaufwand: 8h
import os
import sqlite3
import re

def createEntry(fileName, conn):
    pdbFile = open(fileName, 'r')

    # Define all regular expressions
    reHeader = re.compile('^HEADER\s*(.*)\s*\d{2}-.*-\d{2}\s*(\w*)')
    reTitle = re.compile('^TITLE\s+\d*\s*(.*)')
    reCompnd = re.compile('^COMPND\s+\d?\s*(CHAIN:[^;]*)')
    reAtom = re.compile('^ATOM\s*\d*(\s*[^\s]+\s*){4}(\d+.\d+)\s+(\d+.\d+)\s+(\d+.\d+)')
    
    # Set all values to default
    pdbId = ""
    header = ""
    title = ""
    compnd = list()
    X = 0.0
    Y = 0.0
    Z = 0.0

    # Check each line in the pdb file
    for line in pdbFile.readlines():
        # Try to find a regex match.
        hreg = reHeader.match(line)
        treg = reTitle.match(line)
        creg = reCompnd.match(line)
        areg = reAtom.match(line)

        # Depending on the match, populate one of the variables.
        if hreg:
            header += hreg.group(1).strip()
            pdbId += hreg.group(2)
        elif treg:
            title += treg.group(1)
        elif creg:
            compnd.append(re.sub(' +', ' ', creg.group(1)).strip())
        elif areg:
            X += float(areg.group(2))
            Y += float(areg.group(3))
            Z += float(areg.group(4))

    # Post processing, should there be lots of whitespaces.
    header = re.sub(' +', ' ', header)
    title = re.sub(' +', ' ', title)

    # After fetching all the data from the file, insert the values.
    cur = conn.cursor()
    cur.execute("INSERT INTO protein VALUES(?,?,?)",(pdbId,header,title))
    
    for counter in range(0, len(compnd)):
        cur.execute("INSERT INTO compnd VALUES(?,?,?)",(pdbId,counter,compnd[counter]))

    cur.execute("INSERT INTO atom VALUES(?,?,?,?)",(pdbId,X,Y,Z))
    cur.close()

    
# Open a SQLITE connection to the local db (preconfigured with tables)
conn = sqlite3.connect('pdb_db.db')

for fileName in os.listdir("PDB"):
    createEntry('PDB/'+fileName, conn)

conn.commit()
conn.close()



