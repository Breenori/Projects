import re

#x = re.search("cat", "A cat cannot be friends with a mouse")
#print(x)

eMailFile = open("../UE2_Daten/eMailFile.txt", 'r')

# Other pattern (doesnt work):
#pattern = re.compile("(^|\s)\S+@\S+(\s|$)")
pattern = re.compile("(^\S+@\S+$) | (\s\S+@\S+$) | (^\S+@\S+\s) | (\s\S+@\S+\s)")

for i in eMailFile.readlines():
    print(i)
    result = pattern.findall(i)
    print(result)
eMailFile.close()


referenceFile = open("../UE2_Daten/reference.txt", "r")
pattern = re.compile("^([A-z\.]+)\s+([A-z\.]+)\s+(\d{3}-\d{4})")

for i in referenceFile.readlines():
    result = pattern.search(i)
    if result != None:
        lastname = result.group(1)
        firstname = result.group(2)
        phoneNumber = result.group(3)
        if(phoneNumber != ""):
            print(phoneNumber + ", " + lastname + ", " + firstname)
