#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
struct pq_n {
    int node = 0;
    lli dist = 0, trans = 0;

    pq_n(int n, lli d, lli t) : node(n), dist(d), trans(t) {}
    bool operator>(const pq_n& rhs) const {
        return (this->dist == rhs.dist ? this->trans > rhs.trans:this->dist > rhs.dist);
    }
};

const lli INF = INT64_MAX / 2;
const lli MOD = 1000000009;

int n, m, stt, dest;
vector<vector<pint>> graph;
vector<lli> dist, trans, route_cnt;
priority_queue<pq_n, vector<pq_n>, greater<pq_n>> pq;

/*
* 최단경로를 찾되, 평가 기준에 최단 환승까지 포함.
* 만약 거리와 환승 수가 모두 같으면 현재 노드까지
* 올 수 있는 루트 수 추가.
*/
void dijk() {
    dist[stt] = 0;
    route_cnt[stt] = 1;
    pq.push(pq_n(stt, 0, 0));

    while (!pq.empty()) {
        int cur = pq.top().node;
        lli cur_dist = pq.top().dist;
        lli cur_trans = pq.top().trans;
        pq.pop();

        if (cur_dist <= dist[cur] && cur_trans <= trans[cur]) {
            for (const pint& edge : graph[cur]) {
                lli new_dist = cur_dist + edge.second;
                lli old_dist = dist[edge.first];
                lli new_trans = cur_trans + 1;
                lli old_trans = trans[edge.first];

                if (new_dist < old_dist || (new_dist == old_dist && new_trans < old_trans)) {
                    dist[edge.first] = new_dist;
                    trans[edge.first] = new_trans;
                    route_cnt[edge.first] = route_cnt[cur];
                    pq.push(pq_n(edge.first, new_dist, new_trans));
                }
                else if (new_dist == old_dist && new_trans == old_trans) {
                    route_cnt[edge.first] += route_cnt[cur];
                    route_cnt[edge.first] %= MOD;
                    // 여기서는 평가 값이 업데이트되지 않았으므로 pq push 하지 않음.
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> stt >> dest;

    graph.resize(n + 1);
    dist.resize(n + 1, INF);
    trans.resize(n + 1);
    route_cnt.resize(n + 1);

    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
    }

    dijk();
    if (dist[dest] == INF) {
        cout << -1;
    }
    else {
        cout << dist[dest] << '\n' << trans[dest] << '\n' << route_cnt[dest];
    }

    return 0;
}