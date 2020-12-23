# Übungsabgabe 03
# Sebastian Pritz
# Python Version 3.7.0
# Stundenaufwand: 8h
import sqlite3

# Connect to database.
conn = sqlite3.connect('pdb_db.db')

cur = conn.cursor()
# Execute select statement and print each row.
for row in cur.execute("SELECT p.ID, a.X, a.Y, a.Z FROM protein p JOIN atom a ON a.proteinId=p.ID WHERE p.ID LIKE '%5%'"):
    print(row)

conn.close()