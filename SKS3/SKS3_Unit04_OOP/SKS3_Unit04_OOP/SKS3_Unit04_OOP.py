class Pinboard:
    
    def __init__(self):
        self.__sheet = []

    def __calculatePriority(self, note):
        return  note.count('!') + note.upper().count('WICHTIG') + \
                note.upper().count('DRINGEND') + \
                note.upper().count('EILT')

    def pinOn(self,note):
        self.__sheet.append((self.__calculatePriority(note), note))
        self.__sheet.sort()
        self.__sheet.reverse()

    def __str__(self):
        description = "Notiz \n"
        for z in self.__sheet:
            description += z[1]
            description += "(Prioritaet: " + str(z[0]) + ")\n"
        return description

    def delete(self):
        note = self.__sheet[0][1]
        del self.__sheet[0]
        return note

class Gui:
    __menutext = """
    (N)eue Notiz anheften           (A)lle Notizen auflisten
    (W)ichtigste Notiz entfernen    (E)nde
    """

    def __init__(self, pinboard):
        self.__pb = pinboard

    def run(self):
        choice = ''
        print("Pinnwand")
        while choice not in ['E', 'e']:
            print(self.__menutext)
            choice = input('Ihre Wahl: ')
            if choice in ['N', 'n']: self.__new()
            elif choice in ['A', 'a']: print(self.__pb)
            elif choice in ['W', 'w']: print(self.__pb.delete())
        print("Auf Wiedersehen")

    def __new(self):
        note = input("Notiz: ")
        while note:
            self.__pb.pinOn(note)
            note = input("Notiz: ")

pinboard = Pinboard()
menu = Gui(pinboard)
menu.run()