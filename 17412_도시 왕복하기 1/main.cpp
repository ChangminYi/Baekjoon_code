#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NOT_VISIT = -1;
const int SRC = 1;
const int SINK = 2;

int n, p;
vector<int> graph[401];
int cap[401][401], flow[401][401], par[401];

int main() {
    /**
     * 한 경로에 포함된 길이 다른 경로에 포함되면 안된다는 것은
     * 한 길은 반드시 한 번만 지나야 한다는 것. 이는 용량이 1인 간선임을 뜻하고,
     * 2번 노드까지의 최대 유량을 구하면 서로 다른 경로의 수이다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> p;
    for(int u, v; p--; ) {
        cin >> u >> v;
        graph[u].push_back(v), graph[v].push_back(u);
        cap[u][v] = 1;
    }

    int ans = 0;
    while(true) {
        queue<int> q;
        fill(par + 1, par + n + 1, NOT_VISIT);

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
        int min_flow = INT32_MAX;
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
