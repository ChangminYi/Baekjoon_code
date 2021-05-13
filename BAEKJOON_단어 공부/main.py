def findMax(arg):
    indexList = []
    for i in range(len(arg)):
        if len(indexList) == 0 or arg[i] == arg[indexList[0]]:
            indexList.append(i)
        elif arg[i] > arg[indexList[0]]:
            indexList.clear()
            indexList.append(i)
    return indexList


string = input()
counting = [0 for i in range(26)]
for i in range(len(string)):
    if string[i].islower():
        counting[ord(string[i]) - ord('a')] += 1
    else:
        counting[ord(string[i]) - ord('A')] += 1

ind = findMax(counting)
if len(ind) == 1:
    print(chr(ord('A') + ind[0]))
else:
    print('?')