#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = INT32_MAX / 2;
const int NOT_VISIT = -1;

int n, m, src, sink;
int cap[202][202], flow[202][202], cost[202][202];
int par[202], dist[202];
vector<int> graph[202];
bool in_queue[202];
queue<int> q;

int main() {
    /**
     * 최소 비용 최대 유량이지만, 책의 수를 구하지 않아도 되니 최소 비용만 구하면 된다.
     * A1...An은 src로부터 사람으로 가는 간선의 용량이고,
     * B1...Bn은 서점으로부터 sink로 가는 간선의 용량이다. 둘 다 비용은 0이다.
     * 사람에서 서점으로 가는 간선의 용량은 무한대로 줘도 되지만,
     * 코드에서는 서점에서 sink의 간선 용량으로 설정하였다.
     * 최대 유량을 구하면서 최소 비용을 구하고, 그 비용을 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    src = 0, sink = n + m + 1;
    for(int i = 1; i <= n; i++) {
        cin >> cap[src][i];
        graph[src].push_back(i), graph[i].push_back(src);
    }
    for(int i = n + 1; i <= n + m; i++) {
        cin >> cap[i][sink];
        graph[i].push_back(sink), graph[sink].push_back(i);
    }
    for(int i = n + 1; i <= n + m; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> cost[j][i];
            cost[i][j] = -cost[j][i];
            graph[j].push_back(i), graph[i].push_back(j);
            cap[j][i] = cap[i][sink];
        }
    }

    int min_cost = 0;
    while(true) {
        fill(dist, dist + n + m + 2, INF);
        fill(par, par + n + m + 2, NOT_VISIT);
        
        dist[src] = 0;
        in_queue[src] = true;
        q.push(src);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            in_queue[cur] = false;

            for(const int& nxt: graph[cur]) {
                if(cap[cur][nxt] <= flow[cur][nxt] || dist[cur] + cost[cur][nxt] >= dist[nxt]) continue;
                dist[nxt] = dist[cur] + cost[cur][nxt];
                par[nxt] = cur;

                if(in_queue[nxt]) continue;
                in_queue[nxt] = true;
                q.push(nxt);
            }
        }

        if(par[sink] == NOT_VISIT) break;
        int min_flow = INF;
        for(int i = sink; i != src; i = par[i])
            min_flow = min(min_flow, cap[par[i]][i] - flow[par[i]][i]);
        for(int i = sink; i != src; i = par[i]) {
            min_cost += min_flow * cost[par[i]][i];
            flow[par[i]][i] += min_flow, flow[i][par[i]] -= min_flow;
        }
    }

    cout << min_cost;

    return 0;
}
