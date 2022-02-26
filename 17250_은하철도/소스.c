// #define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int n, m, n1, n2;
int parent[100001], size[100001];

int find_parent(const int x) {
    if (parent[x] == x) return x;
    else return parent[x] = find_parent(parent[x]);
}

void do_union(const int x, const int y) {
    int p_x = find_parent(x), p_y = find_parent(y);
    size[p_x] += size[p_y];
    size[p_y] = 0;
    parent[p_y] = p_x;
}

int main(void) {
    /*
    * 복잡한 컨테이너나 알고리즘이 필요 없기 때문에 C로 구현.
    * union-find를 하면서 집합의 크기도 업데이트한다.
    * 집합이 연결될 때마다 연결된 집합의 크기를 출력하면 된다.
    */

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        scanf("%d", &size[i]);
    }

    do {
        scanf("%d %d", &n1, &n2);
        if (find_parent(n1) != find_parent(n2)) {
            do_union(n1, n2);
        }
        printf("%d\n", size[find_parent(n1)]);
    } while (--m);

    return 0;
}