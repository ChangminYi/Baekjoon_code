#include <iostream>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct edge {
    int n1 = 0, n2 = 0, weight = 0;
    edge(int _n1, int _n2, int _w) : n1(_n1), n2(_n2), weight(_w) {}
    bool operator>(const edge& other) const {
        return this->weight > other.weight;
    }
};

const int MAX = 200000;

int n, m, weight_sum, mst_weight;
int parent[MAX];
priority_queue<edge, vector<edge>, greater<edge>> pq;

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
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 최소 신장 트리의 가중치를 구하는 문제.
    * 절약할 수 있는 최대 비용을 구해야 하므로,
    * 전체 간선의 가중치 합에서 최소 신장 트리의 가중치 합을 뺀 값이 정답.
    * 시간 줄이기 위해 pq는 재활용하지 않았음.
    */
    while (true) {
        cin >> m >> n;
        
        if (n == 0 && m == 0) {
            break;
        }
        else {
            weight_sum = 0;
            mst_weight = 0;
            pq = priority_queue<edge, vector<edge>, greater<edge>>();
            iota(parent, parent + n, 0);

            for (int i = 0, n1, n2, w; i < n; i++) {
                cin >> n1 >> n2 >> w;
                weight_sum += w;
                pq.push(edge(n1, n2, w));
            }

            for (int cnt = 0; cnt < m - 1;) {
                int p_x = find_parent(pq.top().n1);
                int p_y = find_parent(pq.top().n2);
                int w = pq.top().weight;
                pq.pop();

                if (p_x != p_y) {
                    union_elem(p_x, p_y);
                    mst_weight += w;
                    cnt++;
                }
            }

            cout << weight_sum - mst_weight << '\n';
        }
    }

    return 0;
}