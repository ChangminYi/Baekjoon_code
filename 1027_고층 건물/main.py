def get_slope(x1, x2, argi):
    return (argi[x2] - argi[x1]) / (x2 - x1)


num = int(input())
argi = list(map(int, input().split()))
max_count = 0

for i in range(num):
    slope_right = None
    slope_left = None
    visible_right = 0
    visible_left = 0
    
    for j in range(i + 1, num):
        tmp_slope = get_slope(i, j, argi)
        
        if slope_right is None or slope_right < tmp_slope:
            slope_right = tmp_slope
            visible_right += 1

    for j in range(i - 1, -1, -1):
        tmp_slope = get_slope(i, j, argi)
            
        if slope_left is None or slope_left > tmp_slope:
            slope_left = tmp_slope
            visible_left += 1

    max_count = max(max_count, visible_left + visible_right)
    
print(max_count)
