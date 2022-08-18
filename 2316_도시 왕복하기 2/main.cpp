#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NOT_VISIT = -1;
const int INF = 1000000;

int n, p;
vector<int> graph[801];
int cap[801][801], flow[801][801], par[801];

int main() {
    /**
     * 간선의 용량이 아니라 정점의 용량임을 주의해야 한다. 따라서
     * 한 정점을 흐름이 들어오는 곳과 나가는 곳 두 개의 정점으로 분할하고,
     * 1번과 2번 노드를 제외한 곳의 정점 용량을 1로 설정한다. 1, 2번은 무한하다.
     * 간선의 용량은 무한대로 설정하고, 양방향 간선임을 주의해서 그래프를 생성한다.
     * 1번 노드의 입력 노드부터 2번 노드의 출력 노드까지의 최대 유량을 구하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> p;
    for(int i = 1; i <= n; i++) {
        graph[i].push_back(n + i), graph[n + i].push_back(i);
        cap[i][n + i] = (i >= 3 ? 1 : INF);
    }
    for(int u, v; p--; ) {
        cin >> u >> v;
        graph[n + u].push_back(v), graph[v].push_back(n + u);
        graph[n + v].push_back(u), graph[u].push_back(n + v);
        cap[n + u][v] = INF, cap[n + v][u] = INF;
    }

    int SRC = 1, SINK = n + 2;
    int ans = 0;
    while(true) {
        queue<int> q;
        fill(par + 1, par + 2 * n + 1, NOT_VISIT);

        q.push(SRC);
        while(!q.empty() && par[SINK] == NOT_VISIT) {
            int cur = q.front(); q.pop();
            for(const int& nxt: graph[cur]) {
                if(par[nxt] == NOT_VISIT && cap[cur][nxt] > flow[cur][nxt]) {
                    par[nxt] = cur;
                    q.push(nxt);
                    if(nxt == SINK) break;
                }
            }
        }

        if(par[SINK] == NOT_VISIT)
            break;
        int min_flow = INF;
        for(int cur = SINK; cur != SRC; cur = par[cur]) {
            min_flow = min(min_flow, cap[par[cur]][cur] - flow[par[cur]][cur]);
        }
        for(int cur = SINK; cur != SRC; cur = par[cur]) {
            flow[par[cur]][cur] += min_flow, flow[cur][par[cur]] -= min_flow;
        }

        ans += min_flow;
    }

    cout << ans;

    return 0;
}
