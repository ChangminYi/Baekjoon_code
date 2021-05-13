def printarray(arr):
    print('[', end='')
    for i in range(len(arr) - 1):
        print(arr[i], end='')
        print(',', end='')
    print(arr[len(arr) - 1], end='')
    print(']', end='\n')



ITER = int(input())
for i in range(ITER):
    continueFlag = False
    inst = input()
    size = int(input())
    arr = input().lstrip('[').rstrip(']').split(',')
    for j in range(len(inst)):
        if inst[j] == 'R':
            arr.reverse()
            continue
        else:
            if size == 0:
                print("error")
                continueFlag = True
                break
            else:
                del arr[0]
                size -= 1

    if continueFlag:
        continue
    else:
        printarray(arr)

