#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NOT_VISIT = -1;

int t, n, e, a, b;
vector<int> graph[1000], rev_graph[1000];
int cap[1000][1000], flow[1000][1000], par[1000], dp[1000];

int get_max_flow() {
    int ret = 0;
    
    while(true) {
        queue<int> q;
        fill(par, par + n, NOT_VISIT);

        q.push(a);
        while(!q.empty() && par[b] == NOT_VISIT) {
            int cur = q.front(); q.pop();

            for(const int& nxt: graph[cur]) {
                if(par[nxt] == NOT_VISIT && cap[cur][nxt] > flow[cur][nxt]) {
                    par[nxt] = cur;
                    q.push(nxt);
                    if(nxt == b) break;
                }
            }
            for(const int& nxt: rev_graph[cur]) {
                if(par[nxt] == NOT_VISIT && cap[cur][nxt] > flow[cur][nxt]) {
                    par[nxt] = cur;
                    q.push(nxt);
                    if(nxt == b) break;
                }
            }
        }

        if(par[b] == NOT_VISIT) break;
        int min_flow = INT32_MAX;
        for(int i = b; i != a; i = par[i])
            min_flow = min(min_flow, cap[par[i]][i] - flow[par[i]][i]);
        for(int i = b; i != a; i = par[i])
            flow[par[i]][i] += min_flow, flow[i][par[i]] -= min_flow;
        ret += min_flow;
    }

    return ret;
}

int get_single_max(int cur) {
    if(dp[cur] != NOT_VISIT) return dp[cur];
    dp[cur] = 0;
    for(const int& pre: rev_graph[cur]) {
        dp[cur] = max(dp[cur], min(cap[pre][cur], get_single_max(pre)));
    }
    return dp[cur];
}

void clear_var() {
    for(int i = 0; i < n; i++) {
        graph[i].clear();
        rev_graph[i].clear();
        fill(cap[i], cap[i] + n, 0);
        fill(flow[i], flow[i] + n, 0);
    }
    fill(dp, dp + n, NOT_VISIT);
}

int main() {
    /**
     * 1시간 동안 지나갈 수 있는 차의 수를 유량이라고 설정하면,
     * 모든 길을 이용하여 1시간 동안 b에 도착할 수 있는 차의 수는 최대 유량이다.
     * 길 1개를 이용했을 때의 최대 차의 수는 dfs를 통해 구할 수 있다.
     * 최대 유량을 구할 때의 역방향 간선은 dfs에서도 사용할 수 있으므로,
     * 정방향 간선 그래프와 역방향 간선 그래프를 따로 구축한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    (cout << fixed).precision(3);

    cin >> t;
    do {
        cin >> n >> e >> a >> b;
        clear_var();
        for(int u, v; e--; ) {
            cin >> u >> v;
            cin >> cap[u][v];
            graph[u].push_back(v);
            rev_graph[v].push_back(u);
        }

        dp[a] = INT32_MAX;
        cout << (double)get_max_flow() / get_single_max(b) << '\n';
    } while(--t);

    return 0;
}
