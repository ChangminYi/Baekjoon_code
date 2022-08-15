#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NOT_VISIT = -1;

int n, k, d, sp, ep;
vector<int> graph[302];
int capacity[302][302], flow[302][302], parent[302];
queue<int> que;

int main() {
    /**
     * 문제를 네트워크 플로우 문제로 변환해야 한다.
     * 시작점에서 사람(1 ~ n번 노드)로 k만큼, 사람에서 음식(n + 1 ~ n + d)로 1만큼,
     * 음식에서 종점(n + d + 1)까지 양의 제한만큼 간선의 용량이 존재한다.
     * 시작점에서 종점까지의 최대 유량을 구하면 최대 접시의 양과 같다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k >> d;
    sp = 0, ep = n + d + 1;
    for(int i = 1; i <= n; i++) {
        graph[sp].push_back(i), graph[i].push_back(sp);
        capacity[sp][i] = k;
    }
    for(int i = n + 1, w; i <= n + d; i++) {
        cin >> capacity[i][ep];
        graph[i].push_back(ep), graph[ep].push_back(i);
    }
    for(int i = 1, z, f; i <= n; i++) {
        cin >> z;
        while(z--) {
            cin >> f;
            graph[i].push_back(n + f), graph[n + f].push_back(i);
            capacity[i][n + f] = 1;
        }
    }

    int total_flow = 0;
    while(true) {
        fill(parent, parent + n + d + 2, NOT_VISIT);
        while(!que.empty()) que.pop();

        que.push(sp);
        while(!que.empty() && parent[ep] == NOT_VISIT) {
            int cur = que.front(); que.pop();
            for(const int& nxt: graph[cur]) {
                if(capacity[cur][nxt] > flow[cur][nxt] && parent[nxt] == NOT_VISIT) {
                    que.push(nxt);
                    parent[nxt] = cur;
                    if(nxt == ep) break;
                }
            }
        }

        if(parent[ep] == NOT_VISIT)
            break;
        else {
            int avail = INT32_MAX;
            for(int i = ep; i != sp; i = parent[i]) {
                avail = min(avail, capacity[parent[i]][i] - flow[parent[i]][i]);
            }
            for(int i = ep; i != sp; i = parent[i]) {
                flow[parent[i]][i] += avail;
                flow[i][parent[i]] -= avail;
            }
            total_flow += avail;
        }
    }

    cout << total_flow;

    return 0;
}
