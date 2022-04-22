#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int node, weight;
    edge(const int _n = 0, const int _w = 0) : node(_n), weight(_w) {}
};

struct pqn {
    int node;
    long long dist;
    pqn(const int _n, const long long _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) {
        return this->dist > other.dist;
    }
};

const long long INF = INT64_MAX / 2;

int n, m, x, y, z;
vector<edge> graph[100'001];
long long dist[100'001];
priority_queue<pqn, vector<pqn>, greater<>> pq;

long long passing_dijk(const int start, const int dest) {
    fill(dist + 1, dist + n + 1, INF);

    dist[start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const edge& e : graph[cur]) {
                int nxt = e.node;
                int weight = e.weight;
                long long new_dist = cur_dist + weight;
                if (new_dist < dist[nxt]) {
                    dist[nxt] = new_dist;
                    pq.push(pqn(nxt, new_dist));
                }
            }
        }
    }

    return dist[dest];
}

long long non_passing_dijk(const int start, const int dest, const int not_passing) {
    fill(dist + 1, dist + n + 1, INF);

    dist[start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const edge& e : graph[cur]) {
                int nxt = e.node;
                int weight = e.weight;
                long long new_dist = cur_dist + weight;
                if (nxt != not_passing && new_dist < dist[nxt]) {
                    dist[nxt] = new_dist;
                    pq.push(pqn(nxt, new_dist));
                }
            }
        }
    }

    return dist[dest];
}

int main() {
    /*
    * ���ͽ�Ʈ�� �˰����� ����� �ִܰŸ��� ���Ѵ�.
    * y�� �ݵ�� ���İ��� ��δ� x-y ��ο� y-z����� �ִܰŸ��� ���̴�.
    * �� ��� �� �ϳ��� �� �� ���ٸ� ��ü ����� x-y-z�� ���� �Ұ����ϴ�.
    * y�� ��ġ�� �ʴ� ��δ� y�� ������ ��� ��带 Ž�� ������� �Ѵ�.
    * ������ �� ���ٸ� -1�� ����ϰ�, �ƴ϶�� �Ÿ��� ����Ѵ�.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int u, v, w; m > 0; m--) {
        cin >> u >> v >> w;
        graph[u].push_back(edge(v, w));
    }
    cin >> x >> y >> z;

    long long dijk1 = passing_dijk(x, y);
    long long dijk2 = passing_dijk(y, z);
    long long dijk3 = non_passing_dijk(x, z, y);
    cout << (dijk1 != INF && dijk2 != INF ? dijk1 + dijk2 : -1) << ' ' << (dijk3 != INF ? dijk3 : -1);

    return 0;
}