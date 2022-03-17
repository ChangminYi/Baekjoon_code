#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct edge {
    int node, weight;
    edge(const int _n = 0, const int _w = 0) : node(_n), weight(_w) {}
};

struct pqn {
    int node;
    long long dist;
    pqn(const int _n = 0, const long long _d = 0) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) { return dist > other.dist; }
};

const long long INF = INT64_MAX / 2;

int n, m;
vector<edge> graph[100'000];
bool usable[100'000];
long long dist[100'000];
priority_queue<pqn, vector<pqn>, greater<>> pq;

void dijk() {
    fill(dist, dist + n, INF);
    dist[0] = 0;
    pq.push(pqn(0, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const edge& e : graph[cur]) {
                long long new_dist = cur_dist + e.weight;
                if (new_dist < dist[e.node]) {
                    dist[e.node] = new_dist;
                    pq.push(pqn(e.node, new_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���ͽ�Ʈ�� �˰����� ����Ͽ� �ִܰŸ��� ���Ѵ�.
    * ��, �ؼ����� �ִ� n-1��° ���� ������ �湮 �����ϵ��� �����Ѵ�.
    * ������ �Է¹޾��� ��, �� �� �湮 ������ ������� Ȯ�� ��
    * �׷����� ������ �߰��ؾ� �Ѵ�. �Ÿ��� int�� �Ѿ�Ƿ�, long long ���.
    */

    cin >> n >> m;
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        usable[i] = (tmp == 0);
    }
    usable[n - 1] = true;
    for (int n1, n2, t; m; m--) {
        cin >> n1 >> n2 >> t;
        if (usable[n1] && usable[n2]) {
            graph[n1].push_back(edge(n2, t));
            graph[n2].push_back(edge(n1, t));
        }
    }

    dijk();
    cout << (dist[n - 1] == INF ? -1 : dist[n - 1]);

    return 0;
}