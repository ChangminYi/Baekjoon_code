treeNum, minLength = map(int, input().split())
tree = list(map(int, input().split()))
tree.sort(reverse=True)
cutTree = 0
for i in range(1, treeNum):
    cutTree += i * (tree[i-1] - tree[i])
    if cutTree >= minLength:
        for j in range(0, tree[i-1] - tree[i]):
            if cutTree - j * i < minLength:
                print((j - 1) + tree[i])
                i = treeNum
                break