N, K = map(int, input().split())
coin = [0 for i in range(N)]
for i in range(N):
    coin[i]=int(input())
coin.sort(reverse=True)
count = 0
for i in range(N):
    if K // coin[i] > 0:
        count += K // coin[i]
        K %= coin[i]
print(count)