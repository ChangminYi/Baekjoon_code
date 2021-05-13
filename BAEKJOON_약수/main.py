def getnumber(_list):
    return _list[0] * _list[-1]


size = int(input())
if size == 1:
    num = int(input())
    print(num * num)
else:
    nums = list(map(int, input().split()))
    nums.sort()
    print(getnumber(nums))