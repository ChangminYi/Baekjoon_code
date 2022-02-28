#include <iostream>
#include <numeric>

using namespace std;

int v, e, set_cnt;
int parent[3'001], degree[3'001];

int find_parent(const int x) {
    if (parent[x] == x) return x;
    else return parent[x] = find_parent(parent[x]);
}

void union_set(const int x, const int y) {
    parent[find_parent(y)] = find_parent(x);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���Ϸ� ��� & ȸ�� ����. ������ �׷����� ������ Ȧ���� ��尡
    * 0�� ������ ���Ϸ� ȸ�ΰ� �����ϰ�, 2�� ������ ���Ϸ� ��ΰ� �����Ѵ�.
    * ��� ��尡 �湮 ���������� Ȯ���ؾ� �Ѵ�.
    */

    cin >> v >> e;
    iota(parent, parent + v + 1, 0);
    set_cnt = v;
    for (int n1, n2; e; e--) {
        cin >> n1 >> n2;
        degree[n1]++, degree[n2]++;
        if (find_parent(n1) != find_parent(n2)) {
            set_cnt--;
            union_set(n1, n2);
        }
    }

    int deg_cnt = 0;
    for (int i = 1; i <= v; i++) {
        if (degree[i] & 1) deg_cnt++;
    }

    cout << (set_cnt == 1 && (deg_cnt == 0 || deg_cnt == 2) ? "YES" : "NO");

    return 0;
}