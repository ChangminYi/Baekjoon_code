#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

int n, m;
vector<int> dist, parent, degree;
vector<vector<int>> graph, weight;
stack<int> trace;
queue<int> que;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph = vector<vector<int>>(n + 1);
    weight = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
    dist = vector<int>(n + 1, 0);
    parent = vector<int>(n + 1, 0);
    degree = vector<int>(n + 1, 0);
    for (int i = 0, arg1, arg2, val; i < m; i++) {
        cin >> arg1 >> arg2 >> val;
        if (arg1 == 1) {
            dist[arg2] = val;
            parent[arg2] = 1;
        }
        else {
            graph[arg1].push_back(arg2);
            weight[arg1][arg2] = val;
            degree[arg2]++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) {
            que.push(i);
        }
    }
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (int& nxt : graph[cur]) {
            int new_val = dist[cur] + weight[cur][nxt];

            if (dist[nxt] < new_val) {
                dist[nxt] = new_val;
                parent[nxt] = cur;
            }

            if (--degree[nxt] == 0) {
                que.push(nxt);
            }
        }
    }

    trace.push(1);
    while (parent[trace.top()] != 1) {
        trace.push(parent[trace.top()]);
    }
    trace.push(1);

    cout << dist[1] << '\n';
    while (!trace.empty()) {
        cout << trace.top() << ' ';
        trace.pop();
    }

    return 0;
}