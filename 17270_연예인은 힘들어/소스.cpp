#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

struct edge {
    int adj_node = 0;
    long long weight = 0;
    edge(const int _n, const long long _w) : adj_node(_n), weight(_w) {}
};

struct pqn {
    int node = 0;
    long long dist = 0;
    pqn(const int _n, const long long _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const { return this->dist > other.dist; }
};

typedef pair<long long, int> ans_node;

const long long INF = INT64_MAX / 2;

int v, m;
int start[2];
vector<edge> graph[101];
vector<ans_node> cand;
long long dist[2][101];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk(const int start_node, const int idx) {
    fill(dist[idx] + 1, dist[idx] + v + 1, INF);
    dist[idx][start_node] = 0;
    pq.push(pqn(start_node, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[idx][cur]) {
            for (const edge& e : graph[cur]) {
                long long new_dist = cur_dist + e.weight;
                if (new_dist < dist[idx][e.adj_node]) {
                    dist[idx][e.adj_node] = new_dist;
                    pq.push(pqn(e.adj_node, new_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 만나는 노드를 선정하는 조건이 까다로움. 다익스트라 알고리즘을 사용하여
    * 최단거리를 먼저 구한 후, 두 사람의 최단거리의 합의 최솟값을 구함.
    * 최솟값과 거리합이 같은 노드 중에서, 지헌이가 더 가깝거나 같은 노드를 구함.
    * 노드 정보를 저장한 후에 지헌이의 거리, 노드 번호 순서를 기준으로 정렬.
    * 첫 번째 값의 노드 번호를 출려하면 된다.
    */
    cin >> v >> m;
    for (int i = 0, a, b, c; i < m; i++) {
        cin >> a >> b >> c;
        graph[a].push_back(edge(b, c)), graph[b].push_back(edge(a, c));
    }
    cin >> start[0] >> start[1];

    for (int i = 0; i < 2; i++) {
        dijk(start[i], i);
    }

    long long min_dist = INF;
    for (int i = 1; i <= v; i++) {
        if (i != start[0] && i != start[1]) {
            min_dist = min(min_dist, dist[0][i] + dist[1][i]);
        }
    }

    for (int i = 1; i <= v; i++) {
        if (i != start[0] && i != start[1]) {
            if (dist[0][i] + dist[1][i] == min_dist && dist[0][i] <= dist[1][i]) {
                cand.push_back(ans_node(dist[0][i], i));
            }
        }
    }

    if (cand.empty()) {
        cout << -1;
    }
    else {
        sort(cand.begin(), cand.end());
        cout << cand.front().second;
    }

    return 0;
}