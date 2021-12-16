#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;
struct pqn {
    int node = 0, cost = 0;
    pqn(const int _n, const int _c) : node(_n), cost(_c) {}
    bool operator>(const pqn& other) const{
        return this->cost > other.cost;
    }
};

const int INF = INT32_MAX / 2;

int n, m, k;
vector<pint> graph[251];
int dist[251][251];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk(const int start) {
    fill(dist[start] + 1, dist[start] + n + 1, INF);
    dist[start][start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().cost;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (const pint& edge : graph[cur]) {
                int new_dist = cur_dist + edge.second;

                if (new_dist < dist[start][edge.first]) {
                    dist[start][edge.first] = new_dist;
                    pq.push(pqn(edge.first, new_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� u���� v�� �� �� �ִٸ�, ���� �վ�� �ϴ� ���� 0.
    * �� �� ���� ���, �վ�� �ϴ� ���� 1. �� �ǹ� ���̿� �վ��
    * �ϴ� ���� ���� �Ÿ��� �����Ͽ� ��ü ��忡 ���Ͽ� �ִܰŸ��� ã��,
    * �Է¿� ���ؼ� �Ÿ��� ����ϸ� �ȴ�.
    */
    cin >> n >> m;
    for (int i = 0, b, u, v; i < m; i++) {
        cin >> u >> v >> b;
        graph[u].push_back(pint(v, 0));
        graph[v].push_back(pint(u, b == 0 ? 1 : 0));
    }
    for (int i = 1; i <= n; i++) {
        dijk(i);
    }

    cin >> k;
    for (int n1, n2; k > 0; k--) {
        cin >> n1 >> n2;
        cout << dist[n1][n2] << '\n';
    }

    return 0;
}