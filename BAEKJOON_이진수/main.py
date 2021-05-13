N = int(input())
ans0 = 0
ans1 = 1

for i in range(N-1):
    temp0 = ans0 + ans1
    temp1 = temp0
    if i % 2 == 1:
        temp0 -= 1
    ans0 = temp0
    ans1 = temp1

print(ans0)