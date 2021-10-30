#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;
struct pqn {
    pint dist = pint(0, 0);
    int node = 0;
    pqn(pint p, int n) : dist(p), node(n) {}
    bool operator>(const pqn& other) const {
        return this->dist > other.dist;
    }
};

const int INF = INT32_MAX / 2;

int n, m;
vector<vector<pint>> graph;
vector<bool> station_type;
vector<pint> dist;
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk() {
    dist[0] = pint(0, 0);
    pq.push(pqn(dist[0], 0));

    while (!pq.empty()) {
        pint cur_dist = pq.top().dist;
        int cur = pq.top().node;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const pint& edge : graph[cur]) {
                int nxt = edge.first, weight = edge.second;
                pint new_dist = pint(cur_dist.first, cur_dist.second + weight);
                if (station_type[cur] != station_type[nxt]) {
                    new_dist.first++;
                }

                if (new_dist < dist[nxt]) {
                    dist[nxt] = new_dist;
                    pq.push(pqn(new_dist, nxt));
                }
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n);
    station_type.resize(n);
    dist.resize(n, pint(INF, INF));

    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        station_type[i] = (tmp == 0);
    }
    for (int i = 0, tmp; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;

            if (tmp > 0) {
                graph[i].push_back(pint(j, tmp));
            }
        }
    }

    /*
    * 최단 거리 탐색은 다익스트라 알고리즘으로 실행.
    * 단, 우선순위 큐를 사용하기 위한 가중치는
    * 1순위에 환승횟수, 2순위에 소요시간으로 설정.
    */
    dijk();

    cout << dist[m].first << ' ' << dist[m].second;

    return 0;
}