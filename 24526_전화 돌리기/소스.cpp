#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, ans;
vector<int> graph[100'001];
int degree[100'001];
queue<int> que;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 유향 그래프에서, 사이클에 도착할 수 없는 노드를 전부 세야 한다.
    * 그래프의 간선을 모두 방향을 뒤집은 후 위상 정렬을 한다.
    * 정렬에 성공한 노드의 수는 원래 그래프에서 사이클에 도달할 수 없는 노드의 수와 같다.
    * 뒤집힌 그래프에서 방문할 수 없는 노드들은 모두 사이클에 포함된 노드다.
    */

    cin >> n >> m;
    for (int u, v; m; m--) {
        cin >> v >> u;
        graph[u].push_back(v);
        degree[v]++;
    }

    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) {
            ans++;
            que.push(i);
        }
    }
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const int& nxt : graph[cur]) {
            if (--degree[nxt] == 0) {
                ans++;
                que.push(nxt);
            }
        }
    }

    cout << ans;

    return 0;
}