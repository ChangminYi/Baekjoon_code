# DP 방식. 점화식을 이용하여 푼다.
# 1. D[n] = D[n / 3] + 1
# 2. D[n] = D[n / 2] + 1
# 3. D[n] = D[n - 1] + 1


arr = [0 for i in range(1000001)]
num = int(input())
for i in range(2, num + 1):
    arr[i] = arr[i - 1] + 1;
    if i % 2 == 0:
        arr[i] = min(arr[i], arr[i // 2] + 1)
    if i % 3 == 0:
        arr[i] = min(arr[i], arr[i // 3] + 1)
print(arr[num])