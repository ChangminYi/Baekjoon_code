#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
/*
* 거리뿐만이 아니라 이동 수도 같이 저장해야 한다.
*/
struct pq_n {
    lli cost = 0;
    int node = 0, count = 0;

    pq_n(lli c, int n, int cnt) : cost(c), node(n), count(cnt) {}
    bool operator>(const pq_n& rhs) const {
        return this->cost > rhs.cost;
    }
};

const lli INF = INT64_MAX / 2;

int n, m, k, s, d;
int total_accu = 0;
vector<vector<pint>> graph;
vector<vector<lli>> dist;
priority_queue<pq_n, vector<pq_n>, greater<pq_n>> pq;

void dijk() {
    dist[s][0] = 0;
    pq.push(pq_n(0, s, 0));

    while (!pq.empty()) {
        int cur = pq.top().node;
        lli cur_dist = pq.top().cost;
        int cur_cnt = pq.top().count;
        pq.pop();

        if (cur_cnt < n && cur_dist <= dist[cur][cur_cnt]) {
            for (const pint& edge : graph[cur]) {
                int nxt = edge.first;
                int e_weight = edge.second;

                lli new_dist = cur_dist + e_weight;
                lli old_dist = dist[nxt][cur_cnt + 1];
                if (new_dist < old_dist) {
                    dist[nxt][cur_cnt + 1] = new_dist;
                    pq.push(pq_n(new_dist, nxt, cur_cnt + 1));
                }
            }
        }
    }
}

int get_update() {
    lli res = INF;

    for (int i = 1; i <= n; i++) {
        res = min(res, dist[d][i] + (lli)i * total_accu);
    }

    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k >> s >> d;
    graph.resize(n + 1);
    dist.resize(n + 1, vector<lli>(n + 1, INF));
    
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }

    /*
    * 다익스트라는 최초 한 번만 실행한다.
    * 거리만 저장하는 것이 아니고, 최단거리-이동횟수를 같이 저장한다.
    * 세금이 업데이트되면 목적지 노드에서 최단거리+(이동수*세금증가분)의
    * 최솟값을 찾으면 그게 최소 거리이다.
    */
    dijk();
    for (int i = 0, tmp; i <= k; i++) {
        cout << get_update() << '\n';

        if (i < k) {
            cin >> tmp;
            total_accu += tmp;
        }
        else {
            break;
        }
    }

    return 0;
}