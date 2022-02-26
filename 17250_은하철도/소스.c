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
    * ������ �����̳ʳ� �˰����� �ʿ� ���� ������ C�� ����.
    * union-find�� �ϸ鼭 ������ ũ�⵵ ������Ʈ�Ѵ�.
    * ������ ����� ������ ����� ������ ũ�⸦ ����ϸ� �ȴ�.
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