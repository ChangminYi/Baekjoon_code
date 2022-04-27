#include <iostream>
#include <numeric>

using namespace std;

int testcase, n, k, m;
int parent[1'000'000];

int find_parent(const int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

void union_set(const int x, const int y) {
    parent[find_parent(y)] = find_parent(x);
}

int main() {
    /*
    * �� ���� ���̿� ������ �̾��� �ִٸ�, �� ������ �����ϴ� �κ� �׷�����
    * ������ ���� ���� �κ� �׷����� ������ �ȴ�. ���� ���� ������ ����
    * union-find�� ����� �� �ִ�. �׷����� ���� �ʿ� ����.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    for (int i = 1; i <= testcase; i++) {
        cin >> n >> k;
        iota(parent, parent + n, 0);
        for (int a, b; k > 0; k--) {
            cin >> a >> b;
            union_set(a, b);
        }

        cin >> m;
        cout << "Scenario " << i << ":\n";
        for (int u, v; m > 0; m--) {
            cin >> u >> v;
            cout << (find_parent(u) == find_parent(v) ? 1 : 0) << '\n';
        }
        cout << '\n';
    }

    return 0;
}