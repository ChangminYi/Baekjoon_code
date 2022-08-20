#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NOT_VISIT = -1;
const int INF = INT32_MAX / 2;

int n, m;
vector<int> graph[802];
int cap[802][802], flow[802][802], cost[802][802];
int par[802], dist[802];
bool in_queue[802];

int main() {
    /**
     * 최소 비용 최대 유량. 비용을 직원의 월급, 유량을 할 수 있는 일의 수로 설정한다.
     * 간선의 최대 용량은 단방향으로 설정하지만, 그래프가 양방향이므로
     * 간선의 비용도 양방향으로 설정해야 한다. 역방향 간선은 비용이 음수가 된다.
     * 음수 간선에도 동작해야 하므로 SPFA 알고리즘을 사용하여 최단거리를 구하고,
     * 이를 통해서 최대유량을 구하면 최소 비용과 최대 유량을 구할 수 있다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    int src = 0, sink = n + m + 1;

    for(int i = 1; i <= n; i++) {
        graph[src].push_back(i), graph[i].push_back(src);
        cap[src][i] = 1;
    }
    for(int i = n + 1; i <= n + m; i++) {
        graph[i].push_back(sink), graph[sink].push_back(i);
        cap[i][sink] = 1;
    }
    for(int i = 1, num, work, pay; i <= n; i++) {
        cin >> num;
        while(num--) {
            cin >> work >> pay;
            graph[i].push_back(n + work), graph[n + work].push_back(i);
            cap[i][n + work] = 1;
            cost[i][n + work] = pay, cost[n + work][i] = -pay;
        }
    }

    int total_flow = 0, min_cost = 0;
    while(true) {
        fill(par, par + n + m + 2, NOT_VISIT);
        fill(dist, dist + n + m + 2, INF);
        queue<int> q;

        dist[src] = 0;
        in_queue[src] = true;
        q.push(src);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            in_queue[cur] = false;

            for(const int& nxt: graph[cur]) {
                if(cap[cur][nxt] > flow[cur][nxt] && dist[cur] + cost[cur][nxt] < dist[nxt]) {
                    dist[nxt] = dist[cur] + cost[cur][nxt];
                    par[nxt] = cur;
                    if(!in_queue[nxt]) {
                        in_queue[nxt] = true;
                        q.push(nxt);
                    }
                }
            }
        }

        if(par[sink] == NOT_VISIT)
            break;
        int min_flow = INF;
        for(int i = sink; i != src; i = par[i])
            min_flow = min(min_flow, cap[par[i]][i] - flow[par[i]][i]);
        for(int i = sink; i != src; i = par[i]) {
            min_cost += min_flow * cost[par[i]][i];
            flow[par[i]][i] += min_flow, flow[i][par[i]] -= min_flow;
        }
        total_flow += min_flow;
    }

    cout << total_flow << '\n' << min_cost;

    return 0;
}
