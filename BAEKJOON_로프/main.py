num = int(input())
ropes = [int(input()) for i in range(num)]
ropes.sort(reverse=True)
max = 0
for i in range(num):
    if ropes[i] * (i + 1) > max:
        max = ropes[i] * (i + 1)
print(max)