N, K = map(int, input().split())
res = int(1)
if N == K or N == 0:
    print(res)
else:
    for i in range(1, K + 1):
        res *= (N + 1) - i
        res /= i
    print(int(res))
