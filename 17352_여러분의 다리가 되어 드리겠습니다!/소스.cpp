// 17352번: 여러분의 다리가 되어 드리겠습니다!

#include <iostream>
#include <numeric>

using namespace std;

int n;
int parent[300001];

int find_parent(const int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

void union_elem(const int x, const int y) {
    int p_x = find_parent(x), p_y = find_parent(y);
    if (p_x > p_y) {
        swap(p_x, p_y);
    }
    parent[p_y] = p_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    iota(parent + 1, parent + n + 1, 1);

    for (int i = 0, n1, n2; i < n - 2; i++) {
        cin >> n1 >> n2;
        union_elem(n1, n2);
    }

    for (int i = 1, f_par = 0; i <= n; i++) {
        if (parent[i] == i) {
            if (f_par == 0) {
                f_par = i;
            }
            else {
                cout << f_par << ' ' << i;
                break;
            }
        }
    }

    return 0;
}