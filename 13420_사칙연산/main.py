num = int(input())
for i in range(num):
    query = input().split()
    a = int(query[0])
    b = int(query[2])
    ans = int(query[4])
    corr = True

    if query[1] == "+":
        if a + b != ans:
            corr = False
    elif query[1] == "-":
        if a - b != ans:
            corr = False
    elif query[1] == "*":
        if a * b != ans:
            corr = False
    else:
        if a // b != ans:
            corr = False

    if corr:
        print("correct")
    else:
        print("wrong answer")
