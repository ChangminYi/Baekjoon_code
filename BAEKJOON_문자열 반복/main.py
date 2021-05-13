ITER = int(input())
for i in range(0, ITER):
    temp = input().split(' ')
    temp[0] = int(temp[0])
    newStr = ""
    for j in temp[1]:
        for k in range(0, temp[0]):
            newStr += j
    print(newStr)