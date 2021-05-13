num = int(input())
if num == 1:
    pass
else:
    while num != 1:
        for i in range(2, num + 1):
            if num % i == 0:
                print(i)
                num //= i
                break
