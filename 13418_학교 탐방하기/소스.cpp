// 13418번: 학교 탐방하기

#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct pqn {
    int node1 = 0, node2 = 0, weight = 0;
    pqn(const int _n1, const int _n2, const int _w) : node1(_n1), node2(_n2), weight(_w) {}
    const bool operator<(const pqn& other) const {
        return this->weight > other.weight;
    }
    const bool operator>(const pqn& other) const {
        return this->weight < other.weight;
    }
};

int n, m;
vector<int> parent;
priority_queue<pqn, vector<pqn>, less<pqn>> max_pq;
priority_queue<pqn, vector<pqn>, greater<pqn>> min_pq;

int find_parent(const int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

void union_elem(const int x, const int y) {
    int f_x = find_parent(x), f_y = find_parent(y);
    if (f_x > f_y) {
        swap(f_x, f_y);
    }
    parent[f_y] = f_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    parent.resize(n + 1);
    for (int i = 0, n1, n2, w; i <= m; i++) {
        cin >> n1 >> n2 >> w;
        max_pq.push(pqn(n1, n2, w));
        min_pq.push(pqn(n1, n2, w));
    }

    int min_up = 0, max_up = 0;
    iota(parent.begin(), parent.end(), 0);
    for (int cnt = 0; cnt < n; ) {
        int n1 = min_pq.top().node1;
        int n2 = min_pq.top().node2;
        int weight = min_pq.top().weight;
        min_pq.pop();

        if (find_parent(n1) != find_parent(n2)) {
            cnt++;
            if (weight == 0) {
                min_up++;
            }
            union_elem(n1, n2);
        }
    }
    iota(parent.begin(), parent.end(), 0);
    for (int cnt = 0; cnt < n;) {
        int n1 = max_pq.top().node1;
        int n2 = max_pq.top().node2;
        int weight = max_pq.top().weight;
        max_pq.pop();

        if (find_parent(n1) != find_parent(n2)) {
            cnt++;
            if (weight == 0) {
                max_up++;
            }
            union_elem(n1, n2);
        }
    }

    cout << max_up * max_up - min_up * min_up;

    return 0;
}