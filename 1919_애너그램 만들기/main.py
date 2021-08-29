def absolute(a, b):
    if a > b: return a - b
    else: return b - a


temp = [input(), input()]
lst = [[0 for i in range(26)], [0 for i in range(26)]]
for i in range(len(temp)):
    for j in range(len(temp[i])):
        lst[i][ord(temp[i][j]) - ord('a')] += 1

ans = 0
for i in range(26):
    ans += absolute(lst[0][i], lst[1][i])

print(ans)