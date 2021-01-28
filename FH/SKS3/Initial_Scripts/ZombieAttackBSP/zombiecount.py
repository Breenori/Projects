fileZombie = file.open("../../UE_Daten/zombieAttack.txt", "r")

listWords = list()

for i in fileZombie.readlines():
    #print(i)
    splitWordLisxt = i.split(' ')

     #print(splitWordList)
    for i in splitWordList:
        word = i.replace(',' '')
        word = word.replace('\n', '')
        word = word.lower()
        listWords.append(word)
        
print(listWords)

countDict = dict()
for i in listWords:
    if i in countDict:
        countDict[i] += 1
    else:
        countDict[i] = 1

for element in countDict:
    print(element, "....", countDict[element])

fileZombie.close()
