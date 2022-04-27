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
    * 두 정점 사이에 간선이 이어져 있다면, 두 정점을 포함하는 부분 그래프는
    * 간선에 의해 같은 부분 그래프의 집합이 된다. 따라서 간선 정보를 통해
    * union-find를 사용할 수 있다. 그래프를 만들 필요 없음.
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