#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct edge {
    int n1 = 0, n2 = 0, weight = 0;
    edge(int _n1, int _n2, int _w) : n1(_n1), n2(_n2), weight(_w) {}
    bool operator> (const edge& other) const {
        return this->weight > other.weight;
    }
};

int n, m;
vector<int> parent;
priority_queue<edge, vector<edge>, greater<edge>> pq;

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
    iota(parent.begin(), parent.end(), 0);

    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        pq.push(edge(n1, n2, w));
    }

    /*
    * 최소 신장 트리 알고리즘.
    * 간선들 정보를 모두 저장하여 가중치 기준으로 오름차순 정렬하고,
    * 두 노드가 다른 집합이라면 합쳐준 후 가중치를 더함.
    * 이어진 간선이 n-1개가 되면 트리가 완성되므로, 가중치 총합 출력.
    */
    int total_sum = 0;
    for (int i = 0; i < n - 1;) {
        int f1 = find_parent(pq.top().n1);
        int f2 = find_parent(pq.top().n2);
        int weight = pq.top().weight;
        pq.pop();

        if (f1 != f2) {
            union_elem(f1, f2);
            total_sum += weight;
            i++;
        }
    }

    cout << total_sum;

    return 0;
}