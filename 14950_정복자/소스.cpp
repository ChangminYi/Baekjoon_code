#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

struct edge {
    int node1, node2, weight;
    bool operator<(const edge& other) const { return this->weight < other.weight; }
};

int n, m, t, added_val = 0;
long long total_sum = 0;
edge arg[30000];
int parent[10001];

int get_parent(const int x) {
    return parent[x] == x ? x : parent[x] = get_parent(parent[x]);
}

void do_union(const int x, const int y) {
    parent[get_parent(y)] = get_parent(x);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 최소 스패닝 트리를 이용하면 모든 노드를 정복할 수 있다.
    * 크루스칼 알고리즘을 사용하여 MST를 구축하였다.
    * 노드가 연결될 때마다 추가로 더해야 하는 가중치를 높인다.
    */
    cin >> n >> m >> t;
    for (int i = 0; i < m; i++) {
        cin >> arg[i].node1 >> arg[i].node2 >> arg[i].weight;
    }
    sort(arg, arg + m);
    iota(parent + 1, parent + n + 1, 1);

    for (int i = 0, cnt = 0; i < m && cnt < n - 1; i++) {
        if (get_parent(arg[i].node1) != get_parent(arg[i].node2)) {
            cnt++;
            total_sum += arg[i].weight + added_val;
            added_val += t;
            do_union(arg[i].node1, arg[i].node2);
        }
    }

    cout << total_sum;

    return 0;
}