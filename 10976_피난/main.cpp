#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NOT_VISIT = -1;
const int INF = 1000;

int t, n, m;
vector<int> graph[201];
int cap[201][201], flow[201][201], par[201];

void clear_var() {
    for(int i = 1; i <= n; i++) {
        graph[i].clear();
        fill(cap[i] + 1, cap[i] + n + 1, 0);
        fill(flow[i] + 1, flow[i] + n + 1, 0);
    }
}

int main() {
    /**
     * n번 노드에 도달할 수 있는 여왕개미의 수를 유량으로 설정한다. 여왕개미가 총
     * 1000마리 있기 때문에, 1번이나 n번 노드에 연결되면 간선 용량은 1, 아니면 1000이다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    do {
        cin >> n >> m;
        clear_var();
        for(int u, v; m--; ) {
            cin >> u >> v;
            graph[u].push_back(v), graph[v].push_back(u);
            cap[u][v] = (u == 1 || v == n ? 1 : INF);
        }

        int ans = 0;
        while(true) {
            queue<int> q;
            fill(par + 1, par + n + 1, NOT_VISIT);

            q.push(1);
            while(!q.empty() && par[n] == NOT_VISIT) {
                int cur = q.front(); q.pop();
                for(const int& nxt: graph[cur]) {
                    if(par[nxt] == NOT_VISIT && cap[cur][nxt] > flow[cur][nxt]) {
                        par[nxt] = cur;
                        q.push(nxt);
                        if(nxt == n) break;
                    }
                }
            }

            if(par[n] == NOT_VISIT)
                break;
            int min_flow = INT32_MAX;
            for(int cur = n; cur != 1; cur = par[cur]) {
                min_flow = min(min_flow, cap[par[cur]][cur] - flow[par[cur]][cur]);
            }
            for(int cur = n; cur != 1; cur = par[cur]) {
                flow[par[cur]][cur] += min_flow, flow[cur][par[cur]] -= min_flow;
            }

            ans += min_flow;
        }

        cout << ans << '\n';
    } while(--t);
    

    return 0;
}
