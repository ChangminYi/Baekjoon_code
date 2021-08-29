num = int(input())
strs = [input() for i in range(num)]
comp = list(strs[0])

for i in range(len(comp)):
    for j in range(1, num):
        if comp[i] != strs[j][i]:
            comp[i] = '?'
            break

print(''.join(comp))