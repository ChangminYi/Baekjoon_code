num = int(input())
for i in range(num):
    tofind = int(input())
    if tofind == 0:
        print("1 0")
    elif tofind == 1:
        print("0 1")
    else:
        pivonacci = [1 for j in range(tofind)]
        for j in range(2, tofind):
            pivonacci[j] = pivonacci[j - 1] + pivonacci[j - 2]
        print(pivonacci[tofind - 2], pivonacci[tofind - 1])
