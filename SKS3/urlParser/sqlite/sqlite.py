import sqlite3

connection = sqlite3.connect('people.db')

cursor = connection.cursor()

cursor.execute("create table if not exists user(id integer primary key autoincrement, name text, age integer)")

cursor.execute("insert into user values (NULL, 'sebastian pritz', 22)")

#1
cursor.execute("select * from user")
row = cursor.fetchone()
print(row[0])
print(row[1])
print(row[2])

#2 
for rows in cursor.execute("select * from user"):
    print(rows)

#3
liste = cursor.execute("select * from user").fetchall()
print(liste)

cursor.close()
connection.commit()
connection.close()