arr = input().split()
for i in range(1, len(arr) - 1):
    if arr[i - 1] < arr[i] < arr[i + 1]:
        if i == 6:
            print("ascending")
        else:
            continue
    elif arr[i - 1] > arr[i] > arr[i + 1]:
        if i == 6:
            print("descending")
        else:
            continue
    else:
        print("mixed")
        break