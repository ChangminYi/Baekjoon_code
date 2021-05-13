def getans(time):
    answer = [0, 0, 0]    # 0: 300, 1: 60, 2: 10

    answer[0] = time // 300
    time %= 300
    answer[1] = time // 60
    time %= 60
    answer[2] = time // 10

    return answer


T = int(input())
if T % 10 == 0:
    ans = getans(T)
    for i in ans:
        print(i, end=' ')
else:
    print(-1)
