#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;
struct pq_n {
    int node1 = 0, node2 = 0;
    int weight = 0;
    pq_n(int n1, int n2, int w) : node1(n1), node2(n2), weight(w) {}
    bool operator>(const pq_n& rhs) const{
        return this->weight > rhs.weight;
    }
};

constexpr int INF = INT32_MAX / 2;

int n, k;
vector<vector<pint>> mst;
priority_queue<pq_n, vector<pq_n>, greater<pq_n>> pq;
vector<int> parent, dist;

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

void dijk(int start) {
    priority_queue<pint, vector<pint>, greater<pint>> pq;
    fill(dist.begin(), dist.end(), INF);

    dist[start] = 0;
    pq.push(pint(0, start));
    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for(const pint& edge: mst[cur]){
                int nxt = edge.first;
                int e_weight = edge.second;

                int new_dist = cur_dist + e_weight;
                int old_dist = dist[nxt];

                if (new_dist < old_dist) {
                    dist[nxt] = new_dist;
                    pq.push(pint(new_dist, nxt));
                }
            }
        }
    }
}

int find_max_idx() {
    int max_dist = -1, idx = 0;
    
    for (int i = 0; i < n; i++) {
        if (max_dist < dist[i]) {
            max_dist = dist[i];
            idx = i;
        }
    }

    return idx;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    mst.resize(n);
    parent.resize(n);
    dist.resize(n);
    for (int i = 0, n1, n2, w; i < k; i++) {
        cin >> n1 >> n2 >> w;
        pq.push(pq_n(n1, n2, w));
    }
    iota(parent.begin(), parent.end(), 0);

    /*
    * 일단 크루스칼 알고리즘으로 mst를 만든다.
    * 트리에서의 최장거리는 루트 노드에서 가장 먼 노드에서 가장 먼 노드까지의 거리.
    * 다익스트라를 두 번 돌려서 최장거리를 찾아준다.
    */
    int min_total_cost = 0;
    for (int cnt = 0; cnt < n - 1; ) {
        int n1 = pq.top().node1;
        int n2 = pq.top().node2;
        int cur_weight = pq.top().weight;
        pq.pop();

        if (find_parent(n1) != find_parent(n2)) {
            cnt++;
            min_total_cost += cur_weight;
            union_elem(n1, n2);

            mst[n1].push_back(pint(n2, cur_weight));
            mst[n2].push_back(pint(n1, cur_weight));
        }
    }

    dijk(0);
    dijk(find_max_idx());
    int max_dist_idx = find_max_idx();

    cout << min_total_cost << '\n' << dist[max_dist_idx];

    return 0;
}