num = int(input())
for i in range(num):
    sum = int(input())
    stringList = []

    tempRange = sum - 6
    if tempRange < 1:
        tempRange = 1
    for j in range(tempRange, 7):
        if j > sum - j:
            break
        else:
            stringList.append(str("(" + str(j) + "," + str(sum - j) + ")"))

    print(str("Case " + str(i + 1)+ ":"))
    for j in range(len(stringList)):
        print(stringList[j])