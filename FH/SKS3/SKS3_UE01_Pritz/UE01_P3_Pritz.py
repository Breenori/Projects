# Uebungsabgabe 01
# Sebastian Pritz
# Python Version 3.9.0
# Stundenaufwand: 2h

# Initialize variable and list
serial = -1
serialList = list()

# Read as long as 0 isn't typed
while int(serial) != 0:
    serial = input("Bitte Seriennummer eingeben (0 für Ende): ")
    if int(serial) != 0:
        serialList.append(int(serial))
print('\n')

# Since serial numbers are unique, a set is better suited for storing them.
serials = set(serialList)
print("Eingegebene Liste: ", serials)

# Calculate the approximate number of devices based on the values
serie = max(serials) + max(serials)/len(serials) -1
print("Es gibt ungefähr ",serie," Geräte")
