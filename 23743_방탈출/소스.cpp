#include <iostream>
#include <queue>
#include <functional>

using namespace std;

struct edge {
    int n1 = 0, n2 = 0, weight = 0;
    edge(int _n1, int _n2, int _w) : n1(_n1), n2(_n2), weight(_w) {}
    bool operator>(const edge& other) const {
        return this->weight > other.weight;
    }
};

const int MAX = 200001;

int n, m;
int parent[MAX] = { 0 };
priority_queue<edge, vector<edge>, greater<edge>> pq;

int find_parent(const int cur) {
    return parent[cur] == cur ? cur : parent[cur] = find_parent(parent[cur]);
}

void union_elem(const int x, const int y) {
    int p_x = find_parent(x), p_y = find_parent(y);
    parent[p_y] = p_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    
    /*
    * 최소 스패닝 트리로 모든 노드를 연결.
    * 비상탈출구는 0번 노드로 설정. 따라서 총 노드는 n+1개.
    * 만들어진 트리의 가중치 합을 출력하면 된다.
    */
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        pq.push(edge(n1, n2, w));
    }
    for (int i = 1, w; i <= n; i++) {
        cin >> w;
        pq.push(edge(i, 0, w));
        parent[i] = i;
    }

    int sum = 0;
    for (int cnt = 0, n1, n2, weight; cnt < n; ) {
        n1 = pq.top().n1;
        n2 = pq.top().n2;
        weight = pq.top().weight;
        pq.pop();

        if (find_parent(n1) != find_parent(n2)) {
            sum += weight;
            union_elem(n1, n2);
            cnt++;
        }
    }

    cout << sum;

    return 0;
}