#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>

using namespace std;

struct edge {
    int adj_node, weight, corrosion;
    edge(const int _n, const int _w, const int _c) : adj_node(_n), weight(_w), corrosion(_c) {}
};

struct pqn {
    int node, dist, height;
    pqn(const int _n, const int _d, const int _h) : node(_n), dist(_d), height(_h) {}
    bool operator>(const pqn& other) const { return dist > other.dist; }
};

const int INF = INT32_MAX / 2;

int k, n, m, start, desti;
vector<edge> graph[2001];
int dist[201][2001];
priority_queue<pqn, vector<pqn>, greater<>> pq;

void dijk() {
    dist[k][start] = 0;
    pq.push(pqn(start, 0, k));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        int cur_height = pq.top().height;
        pq.pop();

        for (const edge& e : graph[cur]) {
            int nxt = e.adj_node;
            int new_dist = cur_dist + e.weight;
            int new_height = cur_height - e.corrosion;
            if (new_height > 0 && new_dist < dist[new_height][nxt]) {
                dist[new_height][nxt] = new_dist;
                pq.push(pqn(nxt, new_dist, new_height));
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �ִܰŸ��� ���ؾ� ������, �¸� �β� ������ �ɷ�����.
    * ����, �Ÿ��� �β��� ���� �����Ͽ� �ִܰŸ��� ���ؾ� ��.
    * dist�� Ư�� �β��� �ش� ����� �ִܰŸ� �迭�� �����ϰ�,
    * ���ͽ�Ʈ�� �˰������� �ִܰŸ��� ���Ѵ�. �� ��, ������
    * �´� �β� ������ �ִܰŸ��� ã���� �ȴ�.
    */

    cin >> k >> n >> m;
    for (int i = 0, a, b, t, h; i < m; i++) {
        cin >> a >> b >> t >> h;
        graph[a].push_back(edge(b, t, h));
        graph[b].push_back(edge(a, t, h));
    }
    cin >> start >> desti;

    for (int i = 1; i <= k; i++) {
        fill(dist[i] + 1, dist[i] + n + 1, INF);
    }
    dijk();

    int ans = INF;
    for (int i = 1; i <= k; i++) {
        ans = min(ans, dist[i][desti]);
    }

    cout << (ans == INF ? -1 : ans);

    return 0;
}