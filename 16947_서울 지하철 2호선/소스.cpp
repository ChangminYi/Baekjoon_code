#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
int dist[3'001], parent[3'001];
vector<int> graph[3'001];
queue<int> que;
bool flag = false, visit[3'001], in_cycle[3'001];

void bfs() {
    fill(visit + 1, visit + n + 1, false);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const int nxt : graph[cur]) {
            if (!visit[nxt]) {
                visit[nxt] = true;
                dist[nxt] = (in_cycle[nxt] ? 0 : dist[cur] + 1);
                que.push(nxt);
            }
        }
    }
}

void find_cycle(const int cur) {
    visit[cur] = true;
    for (const int nxt : graph[cur]) {
        if (flag) break;
        else {
            if (!visit[nxt]) {
                parent[nxt] = cur;
                find_cycle(nxt);
            }
            else if (nxt != parent[cur]) {
                flag = true;
                in_cycle[cur] = true;
                que.push(cur);
                for (int i = cur; i != nxt; i = parent[i]) {
                    in_cycle[parent[i]] = true;
                }
                break;
            }
            else continue;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 사이클을 먼저 찾아야 하므로, dfs를 실행하여 사이클에 포함된
    * 정점들을 모두 찾아준다. 그리고, 그 중 아무 노드를 큐에 넣고
    * bfs를 실행하면서 사이클로부터의 거리를 구하면 된다.
    */

    cin >> n;
    for (int i = 0, n1, n2; i < n; i++) {
        cin >> n1 >> n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    find_cycle(1);
    bfs();

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << ' ';
    }

    return 0;
}