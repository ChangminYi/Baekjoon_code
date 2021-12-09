#include <iostream>
#include <queue>
#include <functional>

using namespace std;

struct pqn {
    int node1 = 0, node2 = 0, weight = 0;
    pqn(int _n1, int _n2, int _w) : node1(_n1), node2(_n2), weight(_w) {}
    bool operator>(const pqn& other) const {
        return this->weight > other.weight;
    }
};

int n;
int parent[1000];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

int find_parent(const int cur) {
    return parent[cur] == cur ? cur : parent[cur] = find_parent(parent[cur]);
}

void union_elem(const int x, const int y) {
    int p_x = find_parent(x), p_y = find_parent(y);
    if(p_x > p_y){
        swap(p_x, p_y);
    }
    parent[p_y] = p_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 최소 스패닝 트리 문제. 모든 노드를 최소비용으로 이으면 된다.
    * 입력에서 필요한 가중치만 골라서 사용.
    */
    cin >> n;
    for (int i = 0, tmp; i < n; i++) {
        parent[i] = i;
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            if (i < j) {
                pq.push(pqn(i, j, tmp));
            }
        }
    }

    long long sum = 0;
    for (int cnt = 0; cnt < n - 1 && !pq.empty(); ) {
        int n1 = pq.top().node1;
        int n2 = pq.top().node2;
        int weight = pq.top().weight;
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