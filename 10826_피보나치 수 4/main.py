# unsigned long long을 벗어나는 범위라 파이썬으로 계산

N = int(input())
fiv = [0, 1]

if N == 0 or N == 1:
    print(N)
else:
    temp = int(0)
    for i in range(1, N):
        temp = fiv[0] + fiv[1]
        fiv[0] = fiv[1]
        fiv[1] = temp
    print(fiv[1])
