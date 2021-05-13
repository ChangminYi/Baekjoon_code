def getscore(str):
    temp = -1
    sum = 0
    for i in range(len(str)):
        if str[i] == 'O':
            sum += i - temp
        else:
            temp = i
    return sum


num = int(input())
for i in range(num):
    answer = input()
    print(getscore(answer))
