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

    /*
    * union-find를 통해 집합을 구한다. 그리고 서로 다른 두 집단의
    * 대표값을 출력하면 된다.
    */
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