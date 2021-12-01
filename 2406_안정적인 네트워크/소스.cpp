#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;
struct pqn {
    int node1 = 0, node2 = 0;
    int weight = 0;
    pqn(int n1, int n2, int w) : node1(n1), node2(n2), weight(w) {}
    bool operator>(const pqn& other) const {
        return this->weight > other.weight;
    }
};

int n, m;
int pre_union_cnt = 0, total_sum = 0;
vector<pint> edge, to_add;
vector<int> parent;
vector<vector<bool>> used;
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

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

    cin >> n >> m;
    parent.resize(n + 1);
    iota(parent.begin(), parent.end(), 0);
    used.resize(n + 1, vector<bool>(n + 1, false));
    edge.resize(m);

    /*
    * �κ������� �ϼ��� �ּ� ���д� Ʈ�� �ϼ��ϴ� ����.
    * 1�� ���� ��� ��忡 ����Ǿ� �����Ƿ�, �����ϰ� ����.
    * 2������ n�������� ��忡 ���ؼ� mst�� ����µ�,
    * �̸� �����ϴ� �������� �̾��� ��, ������ ���� ��������
    * �켱���� ť�� �����ϰ� mst�� �����. �� �� �ʿ��� ���鵵 ���� �� ���.
    */
    for (pint& e : edge) {
        cin >> e.first >> e.second;
        used[e.first][e.second] = true;
        used[e.second][e.first] = true;

        if (find_parent(e.first) != find_parent(e.second)) {
            union_elem(e.first, e.second);
            pre_union_cnt++;
        }
    }

    for (int i = 1, tmp_w; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> tmp_w;

            if (i >= 2 && j >= 2 && i != j && !used[i][j]) {
                pq.push(pqn(i, j, tmp_w));
            }
        }
    }

    for (int i = pre_union_cnt; i < n - 2;) {
        int n1 = pq.top().node1;
        int n2 = pq.top().node2;
        int w = pq.top().weight;
        pq.pop();

        if (find_parent(n1) != find_parent(n2)) {
            to_add.push_back(pint(n1, n2));
            union_elem(n1, n2);
            total_sum += w;
            i++;
        }
    }

    cout << total_sum << ' ' << to_add.size();
    for (const pint& p : to_add) {
        cout << '\n' << p.first << ' ' << p.second;
    }

    return 0;
}