#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
struct pqn {
    lli dist = 0;
    int node = 0;
    pqn(int n, lli d) : node(n), dist(d) {};
    bool operator>(const pqn& rhs) const {
        return this->dist > rhs.dist;
    }
};

const lli INF = INT64_MAX / 2;

int n, m, d, e;
vector<vector<pint>> graph;
vector<lli> dist_stt, dist_end;
vector<int> height;
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk(int start, vector<lli>& dist) {
    dist[start] = 0;
    pq.push(pqn(start, 0));

    while (!pq.empty()) {
        int cur = pq.top().node;
        lli cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const pint& edge : graph[cur]) {
                int nxt = edge.first;

                /*
                * 각 노드의 높이가 증가하는 방향으로만 탐색.
                */
                if (height[cur] < height[nxt]) {
                    lli new_dist = cur_dist + edge.second;
                    
                    if (new_dist < dist[nxt]) {
                        dist[nxt] = new_dist;
                        pq.push(pqn(nxt, new_dist));
                    }
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> d >> e;

    graph.resize(n + 1);
    dist_stt.resize(n + 1, INF);
    dist_end.resize(n + 1, INF);
    height.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> height[i];
    }
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }

    /*
    * 모든 노드에 다익스트라를 돌리면 시간초과가 나므로,
    * 높이가 증가하다가 감소해야 하는 조건을 이용하여
    * 1번과 n번 노드에서 높이가 증가하는 방향으로만 다익스트라를 실행.
    * i번 노드에서 보면, 1~i까지는 증가하고, i~n번까지는 감소하는 경로의
    * 최소 거리를 알 수 있다. 그 후에 각 노드마다 값을 계산하면 된다.
    */
    dijk(1, dist_stt);
    dijk(n, dist_end);

    lli max_val = INT64_MIN;
    for (int i = 2; i <= n - 1; i++) {
        if (dist_stt[i] != INF && dist_end[i] != INF) {
            lli tmp = (lli)e * height[i] - d * (dist_stt[i] + dist_end[i]);

            max_val = max(max_val, tmp);
        }
    }

    if (max_val == INT64_MIN) {
        cout << "Impossible";
    }
    else {
        cout << max_val;
    }

    return 0;
}