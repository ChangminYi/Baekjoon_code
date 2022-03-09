#include <iostream>
#include <numeric>

using namespace std;

struct edge {
    int node1, node2;
};

int n, m, k;
edge arg[10'000];
int parent[1'001];
bool usable[10'000];

int find_parent(const int x) {
    if (parent[x] == x) return x;
    else return parent[x] = find_parent(parent[x]);
}

void union_set(const int x, const int y) {
    parent[find_parent(y)] = find_parent(x);
}

int make_mst() {
    int cnt = 0, mst_weight = 0;
    bool erased = false;
    iota(parent, parent + n + 1, 0);

    for (int i = 0; i < m && cnt < n - 1; i++) {
        if (usable[i] && find_parent(arg[i].node1) != find_parent(arg[i].node2)) {
            cnt++;
            mst_weight += i + 1;
            union_set(arg[i].node1, arg[i].node2);
            if (!erased) {
                erased = true;
                usable[i] = false;
            }
        }
    }

    return (cnt == n - 1 ? mst_weight : 0);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ������ ����ġ�� ������ �ε��� + 1�� ������ �� �ִ�.
    * ������������ �̸� ���ĵǾ� ������ ������ ���� �������� �ʴ´�.
    * �������� �־��� ���ǿ� �°� mst�� ����鼭 ������ �ϳ��� �����,
    * ó������ ���� �� ���� �������� ��� 0�� ����ϰ� �����Ѵ�.
    */

    cin >> n >> m >> k;
    fill(usable, usable + m, true);
    for (int i = 0; i < m; i++) {
        cin >> arg[i].node1 >> arg[i].node2;
    }

    for (int i = 0, res; i < k; i++) {
        if (res = make_mst()) {
            cout << res << ' ';
        }
        else {
            for (int j = i; j < k; j++) {
                cout << "0 ";
            }
            break;
        }
    }

    return 0;
}