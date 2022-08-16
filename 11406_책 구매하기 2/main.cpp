#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NOT_VISIT = -1;

int n, m, sp = 0, ep;
vector<int> graph[202];
int capacity[202][202], flow[202][202], par[202];

int main() {
    /**
     * 0번 노드를 흐름의 시작점으로 설정한다. 1 ~ n번 노드는 사람으로 설정하고,
     * 0번 노드로부터의 간선 용량은 사려고 하는 책의 개수로 설정한다.
     * n + 1 ~ n + m번 노드는 서점으로 설정하고, 사람으로부터의 용량은 사람 당 구매 가능한
     * 책의 최대 개수로 설정한다. n + m + 1번 노드를 싱크로 설정하여 싱크 노드로
     * 갈 수 있는 최대 유량을 구하면 최대 구매 가능한 책의 수가 된다. 
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    ep = n + m + 1;
    for(int i = 1; i <= n; i++) {
        cin >> capacity[sp][i];
        graph[sp].push_back(i), graph[i].push_back(sp);
    }
    for(int i = n + 1; i <= n + m; i++) {
        cin >> capacity[i][ep];
        graph[i].push_back(ep), graph[ep].push_back(i);
    }
    for(int i = n + 1; i <= n + m; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> capacity[j][i];
            if(capacity[j][i])
                graph[j].push_back(i), graph[i].push_back(j);
        }
    }

    int total_flow = 0;
    while(true) {
        queue<int> que;
        fill(par, par + n + m + 2, NOT_VISIT);

        que.push(sp);
        while(!que.empty() && par[ep] == NOT_VISIT) {
            int cur = que.front(); que.pop();
            for(const int& nxt: graph[cur]) {
                if(par[nxt] == NOT_VISIT && capacity[cur][nxt] > flow[cur][nxt]) {
                    par[nxt] = cur;
                    que.push(nxt);
                    if(nxt == ep) break;
                }
            }
        }
        
        if(par[ep] == NOT_VISIT)
            break;
        int tmp_flow = INT32_MAX;
        for(int i = ep; i != sp; i = par[i]) {
            tmp_flow = min(tmp_flow, capacity[par[i]][i] - flow[par[i]][i]);
        }
        for(int i = ep; i != sp; i = par[i]) {
            flow[par[i]][i] += tmp_flow, flow[i][par[i]] -= tmp_flow;
        }
        total_flow += tmp_flow;
    }

    cout << total_flow;

    return 0;
}
