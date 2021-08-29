m_val = -1
m_ind = 0
lst = [0 for i in range(9)]
for i in range(len(lst)):
    lst[i] = int(input())
    if m_val < lst[i]:
        m_val = lst[i]
        m_ind = i
print(m_val)
print(m_ind + 1)