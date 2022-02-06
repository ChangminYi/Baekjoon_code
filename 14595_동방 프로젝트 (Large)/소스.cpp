#include <iostream>
#include <numeric>

using namespace std;

int n, m, x, y;
int parent[1'000'001];

int do_find(const int x) {
    return parent[x] == x ? x : parent[x] = do_find(parent[x]);
}

void do_union(const int x, const int y) {
    int f_x = do_find(x), f_y = do_find(y);
    if (f_x < f_y) parent[f_x] = f_y;
    else parent[f_y] = f_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �и��������� ���� �㹰���� ���¸� ǥ���� �� �ִ�.
    * ������ ��ǩ���� ���� �� ���� ū ������ �����Ѵ�.
    * x�� y�� ������ ������ ������ union�Ѵ�. union�� �� ���� ũ�⸦ �ϳ� ���δ�.
    * ��� ������ ������ �� n���� �����ִ� ���� ���̴�.
    */
    cin >> n >> m;
    iota(parent + 1, parent + n + 1, 1);

    while (m--) {
        cin >> x >> y;
        int fx, fy = do_find(y);
        while ((fx = do_find(x)) != fy) {
            do_union(do_find(x), do_find(x) + 1);
            n--;
        }
    }

    cout << n;

    return 0;
}