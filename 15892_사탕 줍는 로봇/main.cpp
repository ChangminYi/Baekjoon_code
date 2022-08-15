#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NOT_VISIT = -1;

int n, m;
vector<int> graph[301];
bool is_added[301][301];
int capacity[301][301], flow[301][301], parent[301];

int main() {
    /**
     * 네트워크 플로우 문제. 로봇의 수를 유량으로 설정하면 된다.
     * 입력에서 간선의 중복을 조심하면 된다. 용량은 전부 더해준다.
     */
    
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for(int u, v, w; m--; ) {
        cin >> u >> v >> w;
        capacity[u][v] += w, capacity[v][u] += w;
        if(!is_added[u][v]) {
            is_added[u][v] = is_added[v][u] = true;
            graph[u].push_back(v), graph[v].push_back(u);
        }
    }

    int total_flow = 0;
    while(true) {
        queue<int> que;
        fill(parent + 1, parent + n + 1, NOT_VISIT);

        que.push(1);
        while(!que.empty() && parent[n] == NOT_VISIT) {
            int cur = que.front(); que.pop();
            for(const int& nxt: graph[cur]) {
                if(parent[nxt] == NOT_VISIT && capacity[cur][nxt] > flow[cur][nxt]) {
                    parent[nxt] = cur;
                    que.push(nxt);
                    if(nxt == n) break;
                }
            }
        }

        if(parent[n] == NOT_VISIT) break;
        int avail = INT32_MAX;
        for(int i = n; i != 1; i = parent[i]) {
            avail = min(avail, capacity[parent[i]][i] - flow[parent[i]][i]);
        }
        for(int i = n; i != 1; i = parent[i]) {
            flow[parent[i]][i] += avail;
            flow[i][parent[i]] -= avail;
        }
        total_flow += avail;
    }

    cout << total_flow;

    return 0;
}
