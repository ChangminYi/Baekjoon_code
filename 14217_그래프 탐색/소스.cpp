#include <iostream>
#include <queue>

using namespace std;

int n, m, q;
int dist[501];
bool visit[501], adj[501][501];
queue<int> que;

void bfs() {
    fill(dist + 1, dist + n + 1, -1);
    fill(visit + 1, visit + n + 1, false);

    visit[1] = true;
    dist[1] = 0;
    que.push(1);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (int i = 2; i <= 500; i++) {
            if (adj[cur][i] && !visit[i]) {
                visit[i] = true;
                dist[i] = dist[cur] + 1;
                que.push(i);
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int n1, n2; m; m--) {
        cin >> n1 >> n2;
        adj[n1][n2] = adj[n2][n1] = true;
    }
    cin >> q;
    for (int inst, n1, n2; q; q--) {
        cin >> inst >> n1 >> n2;
        adj[n1][n2] = adj[n2][n1] = (inst == 1);

        bfs();
        for (int i = 1; i <= n; i++) {
            cout << dist[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}