#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

struct edge {
    int node1, node2, weight;
};

int p, w, c, v;
int parent[1'001];
edge arg[50'000];

int find_parent(const int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

void union_set(const int x, const int y) {
    parent[find_parent(y)] = find_parent(x);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * union-find�ε� Ǯ �� �ְ�, �Ű����� Ž�����ε� Ǯ �� �ִ�.
    * union-find�� Ǯ ���, ��� ������ ����ġ �������� �������� �����Ͽ�
    * c�� v�� ���� ������ �� ������ �� ��带 ��ģ��. �������� ���� ������
    * ����ġ�� ���� ���� ���� �ʺ��̴�.
    * �Ű����� Ž������ Ǯ ���, ������ �� �ִ� �ִ� �ʺ� ��������
    * bfs�� �����Ͽ� �̺� Ž���� �����Ѵ�.
    * union-find�� �Ű����� Ž������ �� �� ������.
    */

    cin >> p >> w >> c >> v;
    iota(parent, parent + p, 0);
    for (int i = 0; i < w; i++) {
        cin >> arg[i].node1 >> arg[i].node2 >> arg[i].weight;
    }

    sort(arg, arg + w,
        [](edge& lhs, edge& rhs) {
            return lhs.weight > rhs.weight;
        });

    for (int i = 0; i < w; i++) {
        union_set(arg[i].node1, arg[i].node2);
        if (find_parent(c) == find_parent(v)) {
            cout << arg[i].weight;
            break;
        }
    }

    return 0;
}