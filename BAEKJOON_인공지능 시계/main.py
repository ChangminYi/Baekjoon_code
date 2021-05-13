Hour, Min, Sec = map(int, input().split())
add = int(input())

Sec += add % 60
add //= 60
if Sec >= 60:
    Sec -= 60
    Min += 1
Min += add % 60
add //= 60
if Min >= 60:
    Min -= 60
    Hour += 1
Hour += add % 24
if Hour >= 24:
    Hour -= 24

print(Hour, Min, Sec)
