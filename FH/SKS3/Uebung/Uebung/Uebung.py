
import sqlite3
import statistics

files = [open('umfrage_daten_part1.csv'),open('umfrage_daten_part2.csv')]
files[0].readline()
def getdata(file):
    data = list()
    for line in file.readlines():
        data.append(line.split(';'))
        data[-1][4]=int(data[-1][4])
        data[-1][5]=int(data[-1][5])
        data[-1][6]=int(data[-1][6])
        data[-1][7]=int(data[-1][7])
        data[-1][8]=int(data[-1][8])

    for line in file.readlines():
        data.append(line.split(';'))
        data[-1][4]=int(data[-1][4])
        data[-1][5]=int(data[-1][5])
        data[-1][6]=int(data[-1][6])
        data[-1][7]=int(data[-1][7])
        data[-1][8]=int(data[-1][8])


    male = 0
    female = 0
    for entry in data:
        if entry[1]=='weiblich':
            female += 1
        elif entry[1]=='männlich':
            male += 1


    maleba = 0
    malema = 0
    femaleba = 0
    femalema = 0
    for entry in data:
        if entry[3]=='Bachelorstudium':
            if entry[1]=='weiblich':
                femaleba += 1
            elif entry[1]=='männlich':
                maleba += 1
        elif entry[3]=='Masterstudium':
            if entry[1]=='weiblich':
                femalema += 1
            elif entry[1]=='männlich':
                malema += 1

    femlist = list()
    for entry in data:
        if entry[1]=='weiblich':
            femlist.append(entry[4]+entry[5]+entry[6]+entry[7]+entry[8])

    return [female, male, femaleba, maleba, femalema, malema, statistics.mean(femlist)]


conn = sqlite3.connect('results.db')
cur = conn.cursor()

cur.execute("""
    CREATE TABLE if not exists statistics (
        id integer PRIMARY KEY AUTOINCREMENT,
        numberFemale integer,
        numberMale integer,
        numberBachelorFemale integer,
        numberBachelorMale integer,
        numberMasterFemale integer,
        numberMasterMale integer,
        meanPsychologicalFemale real
    )
""")

for file in files:
    data = getdata(file)

    cur.execute(
        """INSERT INTO statistics(numberFemale,numberMale,
    numberBachelorFemale,numberBachelorMale,
    numberMasterFemale,numberMasterMale,
    meanPsychologicalFemale) values(?,?,?,?,?,?,?)
    """,(data[0],data[1],data[2],data[3],data[4],data[5],data[6]))

cur.close()
conn.commit()
