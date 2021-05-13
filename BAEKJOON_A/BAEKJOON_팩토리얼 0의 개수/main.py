ind = int(input())
count_2 = int(0)
count_5 = int(0)
if ind == 0:
    print(0)
else:
    for i in range(1, ind + 1):
        temp = i
        while temp % 2 == 0:
            temp /= 2
            count_2 += 1
        while temp % 5 == 0:
            temp /= 5
            count_5 += 1
    if count_2 < count_5:
        print(count_2)
    else:
        print(count_5)
