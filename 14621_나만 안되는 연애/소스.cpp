#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct edge {
    int node1 = 0, node2 = 0, cost = 0;
    edge(int n1, int n2, int c) : node1(n1), node2(n2), cost(c) {}
    bool operator>(const edge& other) const {
        return this->cost > other.cost;
    }
};

int n, m, mst_size = 0, total_cost = 0;
vector<bool> is_men;
vector<int> parent;
priority_queue<edge, vector<edge>, greater<edge>> pq;

/*
* union-find의 find
*/
int find_parent(int x) {
    return (parent[x] == x ? x : parent[x] = find_parent(parent[x]));
}

/*
* union-find의 union: 낮은 parent 값으로 최적화
*/
void union_elem(int x, int y) {
    int f_x = find_parent(x), f_y = find_parent(y);

    if (f_x > f_y) {
        swap(f_x, f_y);
    }
    parent[f_y] = f_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    is_men.resize(n + 1);
    parent.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        char tmp;
        cin >> tmp;
        is_men[i] = (tmp == 'M');
        parent[i] = i;
    }
    /*
    * 양 끝의 노드의 종류가 다른 엣지들만 평가하면 된다.
    */
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        if (is_men[n1] != is_men[n2]) {
            pq.push(edge(n1, n2, w));
        }
    }

    /*
    * 최소 스패닝 트리 구축.
    */
    while (!pq.empty() && mst_size < n - 1) {
        int n1 = pq.top().node1, n2 = pq.top().node2;
        int f_n1 = find_parent(n1), f_n2 = find_parent(n2);
        int cost = pq.top().cost;
        pq.pop();

        if (f_n1 != f_n2) {
            mst_size++;
            total_cost += cost;
            union_elem(f_n1, f_n2);
        }
    }

    cout << (mst_size == n - 1 ? total_cost : -1);

    return 0;
}