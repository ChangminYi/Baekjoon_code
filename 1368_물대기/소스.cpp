#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct pq_n{
    int node1 = 0, node2 = 0;
    int cost = 0;
    pq_n(int n1, int n2, int c) : node1(n1), node2(n2), cost(c) {}
    bool operator> (const pq_n& rhs) const {
        return this->cost > rhs.cost;
    }
};

int n;
vector<int> parent;
priority_queue<pq_n, vector<pq_n>, greater<pq_n>> pq;

int find_parent(int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

void union_elem(int x, int y) {
    int f_x = find_parent(x);
    int f_y = find_parent(y);

    if (f_x > f_y) {
        swap(f_x, f_y);
    }

    parent[f_y] = f_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    parent.resize(n + 1);
    iota(parent.begin(), parent.end(), 0);

    /*
    * 우물을 파는 행위를 더미 노드로 간주, 0번 할당
    * 총 노드는 n+1개가 되고, n개의 간선을 연결해야 한다.
    * 나머지 과정은 mst를 만들기만 하면 된다.
    */
    for (int i = 1, w; i <= n; i++) {
        cin  >> w;

        pq.push(pq_n(0, i, w));
    }
    for (int i = 1, w; i <= n; i++){
        for (int j = 1; j <= n; j++) {
            cin >> w;

            if (i < j) {
                pq.push(pq_n(i, j, w));
            }
        }
    }

    int total_cost = 0;
    for (int cnt = 0; cnt < n && !pq.empty(); ) {
        int n1 = pq.top().node1;
        int n2 = pq.top().node2;
        int edge_w = pq.top().cost;
        pq.pop();

        if (find_parent(n1) != find_parent(n2)) {
            total_cost += edge_w;
            union_elem(n1, n2);
            cnt++;
        }
    }

    cout << total_cost;

    return 0;
}