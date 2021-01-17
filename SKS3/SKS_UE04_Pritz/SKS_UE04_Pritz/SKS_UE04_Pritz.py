# Übungsabgabe 04
# Sebastian Pritz
# Python Version 3.7.0
# Stundenaufwand: 4h

import re

class SkiOverview:

    # Default constructor creates all the necessary nationality classes in a dictionary
    def __init__(self):
        self.__nationalities = dict()
        self.__nationalities["AUT"]=Nationality("AUT")
        self.__nationalities["GER"]=Nationality("GER")
        self.__nationalities["USA"]=Nationality("USA")

    # str function delegates to nationality string function 
    # and concatenates all lines
    def __str__(self):
        allLines = " "
        for nat in self.__nationalities.keys():
            allLines += nat + ': ' + str(self.__nationalities[nat]) + "\n"
        return allLines
    
    # Function to reliably read a number from user input
    def __readNumber(self, msg):
        num = " "
        while not num.isnumeric():
            num = input(msg)
        return int(num)

    # Interactive dialogue to create a person
    def createPerson(self):
        nat = ""
        while nat not in["AUT","GER","USA"]:
            nat = input("Welcher Nation wollen Sie eine Person hinzufuegen [AUT, GER, USA]: ")
        name = input("Wie lautet der Name der Person: ")
        age = input("Wie alt ist die Person: ")
        gold = self.__readNumber("Wie viele Goldmedaillen hat die Person erreicht: ")
        silver = self.__readNumber("Wie viele Silbermedaillen hat die Person erreicht: ")
        bronze = self.__readNumber("Wie viele Bronzemedaillen hat die Person erreicht: ")
        # After data aquisition, create the person and add it to the list.
        self.__nationalities[nat].addPerson(Person(name,age,(gold,silver,bronze),nat))

    # Dialogue for option (A)
    def printAll(self):
        answer = ' '
        while answer not in ['1','2','3']:
            answer = input("""Bitte Gesamtstatistik der Medaillen angeben 
            (1: Anzahl von Medaillen pro Person einer Nationalitaet, 
             2: Anzahl der Gold-, Silber-und Bronzemedaillen aller Rennfahrer einer Nationalitaet, 
             3: Anzahl aller Medaillen aller Nationalitäten):""")

        # Only option 1 and 2 require a nationality
        nationality = " "
        if answer != '3':
            while nationality  not in ['AUT', 'GER', 'USA']:
                nationality  = input("Bitte Nationalitaet auswaehlen [AUT, GER, USA]: ")
        
        # based on the answer, delegate to another function
        if answer == '1':
            self.__nationalities[nationality].printMedalsPerPerson()
        elif answer == '2':
            self.__nationalities[nationality].printTotalMedals()
        elif answer == '3':
            self.__printTotalMedals()
    
    # removes the person with the least medals
    def removePerson(self):
        nationality = " "
        while nationality  not in ['AUT', 'GER', 'USA']:
            nationality  = input("Bitte Nationalitaet auswaehlen [AUT, GER, USA]: ")

        if nationality in self.__nationalities.keys():
            allPeople = self.__nationalities[nationality].getPeople()
            # iterates through all people of specified nationality to determine the one with least medals
            if len(allPeople) > 0:
                tmp = allPeople[0]
                for p in allPeople:
                    if p.getTotalMedals() < tmp.getTotalMedals():
                        tmp = p
                # then - remove it.
                self.__nationalities[nationality].removePerson(tmp)
            else:
                print("Nationalitaet hat keine Eintraege. Loeschen nicht moeglich.")
        else:
            print("Fehler. Bitte waehlen Sie entweder 'AUT', 'GER' oder 'USA'.")
    
    # Gets total medals of all nationalities through delegation
    def __printTotalMedals(self):
        totalMedals = 0
        for nat in self.__nationalities.keys():
            totalMedals += self.__nationalities[nat].getTotalMedals()
        print("Alle: " + str(totalMedals))

    # reads in the ski racers from the files that were given to us
    def populateFromFiles(self):
        defaultFolder = "src/"
        defaultFiles = ("AUT_Rennfahrer.txt","GER_Rennfahrer.txt","USA_Rennfahrer.txt")
        for file in defaultFiles:
            curFile = open(defaultFolder + file, 'r')
            for line in curFile.readlines():
                elements = re.split(r'\t+', line.rstrip('\t'))
                if len(elements)==6:
                    self.__nationalities[elements[0]].addPerson(Person(elements[1],(int)(elements[2]),((int)(elements[3]),(int)(elements[4]),(int)(elements[5])),elements[0]))

            curFile.close()

class Person:

    # constructor to create a person
    def __init__(self, name, age, medals, nationality="-"):
        self.__name = name
        self.__age = age
        self.__nationality=nationality
        self.__medals = medals

    # Str function for person
    def __str__(self):
        pString = self.__nationality + "\t" + '{:<30}'.format(p.getName()) + str(self.__age) + "\t"
        for medal in self.__medals:
            pString += "\t" + str(medal)
        return pString

    def getName(self):
        return self.__name
    
    def getAge(self):
        return self.__age

    def getNationality(self):
        return self.__nationality

    def getMedals(self):
        return self.__medals

    # Add up all medals and return them = total medals
    def getTotalMedals(self):
        totalMedals = 0
        for medal in self.__medals:
            totalMedals += medal
        return totalMedals

class Nationality:

    # constructor for nationality. start with an empty list of people.
    def __init__(self, nationality):
        self.__nationality = nationality
        self.__people = list()

    # str function fro nationality. Delegates to Person to display the nationality and all of the associated people
    def __str__(self):
        pstring = ""
        for p in self.__people:
            pstring += str(p) + "\n"
        return pstring

    def getNationality(self):
        return self.__nationality

    def getPeople(self):
        return self.__people

    # Add a person to the nationality. 
    def addPerson(self, person):
        # Can only add a person to the list. Other datatypes wouldnt make sense
        if isinstance(person, Person):
            self.__people.append(person)
        else:
            print("Argument 1 must be a person.")

    def removePerson(self, person):
        self.__people.remove(person)

    # Loop through all people and print a line for each of them
    def printMedalsPerPerson(self):
        for p in self.__people:
            print(str(p.getAge()) + "\t" + '{:<30}'.format(p.getName()) + str(p.getTotalMedals()))
    
    # Print the amount of medals for the entire nationality (all people in it)
    def printTotalMedals(self):
        print(self.__nationality + "\t" + str(self.getTotalMedals()))

    def getTotalMedals(self):
        totalMedals = 0
        for p in self.__people:
            totalMedals += p.getTotalMedals()
        return totalMedals


class SkiGUI:
    # Standard menu text
    __guitext = """
    (N)eue Person einer Nationalitaet hinzufügen     (L)oeschen eines Rennfahres mit den 
                                                     wenigsten Medaillen einer Nationalitaet
    (A)lle Personen einer Nationalitaet anzeigen     (E)nde der Rennlaeuferansicht
    """

    # Create a SkiOverview to hold the data
    def __init__(self):
        self.__skio = SkiOverview() 
        self.__skio.populateFromFiles()

    def run(self):
        # Interactive UI
        print("Karder Ansicht - Rennlaeufer der Nationalitaeten AUT, GER und USA")
        choice = ' '
        while choice not in ['E','e']:
            print(self.__guitext)
            choice = input('Ihre Wahl: ')
            if choice in ['N','n']:
                self.__skio.createPerson()
            elif choice in ['L','l']:
                self.__skio.removePerson()
            elif choice in ['A','a']:
                self.__skio.printAll()
            print("\n")

gui = SkiGUI()
gui.run()