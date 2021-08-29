def equation(num):
    return 3 * num * (num + 1) + 1


num = int(input())
if num == 1:
    print('1')
else:
    count = 1
    while num > equation(count):
        count += 1
    print(count + 1)