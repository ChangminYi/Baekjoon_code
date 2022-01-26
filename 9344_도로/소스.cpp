#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

struct edge {
    int node_l = 0, node_r = 0, weight = 0;
    bool operator<(const edge& other) const { return this->weight < other.weight; }
};

int t, n, m, p, q;
int parent[100001];
edge arg[200000];

int get_parent(const int x) {
    return parent[x] == x ? x : parent[x] = get_parent(parent[x]);
}

void union_elem(const int x, const int y) {
    int p_x = get_parent(x), p_y = get_parent(y);
    parent[p_y] = p_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �ּ� ���д� Ʈ�� ����. �ϼ��� mst�� ����ġ ���� ���� �ʿ�� ����.
    * ũ�罺Į �˰����� ����Ͽ���. �� ������ �մ� ����, p�� q�� �̾����ٸ�
    * yes�� ����ϰ�, Ʈ���� �ϼ����� ������ �̾����� �ʴ´ٸ� no ���.
    */
    cin >> t;
    do {
        bool connected = false;
        cin >> n >> m >> p >> q;
        if (p > q) swap(p, q);
        iota(parent + 1, parent + n + 1, 1);
        for (int i = 0; i < m; i++) {
            cin >> arg[i].node_l >> arg[i].node_r >> arg[i].weight;
            if (arg[i].node_l > arg[i].node_r) swap(arg[i].node_l, arg[i].node_r);
        }

        sort(arg, arg + m);

        for (int i = 0, cnt = 0; i < m && cnt < n - 1 && !connected; i++) {
            if (get_parent(arg[i].node_l) != get_parent(arg[i].node_r)) {
                if (arg[i].node_l == p && arg[i].node_r == q) {
                    connected = true;
                    break;
                }
                else {
                    cnt++;
                    union_elem(arg[i].node_l, arg[i].node_r);
                }
            }
        }

        cout << (connected ? "YES\n" : "NO\n");
    } while (--t);

    return 0;
}