#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<bool> visit;

bool dfs(int cur, int depth) {
    if (depth == 4) {
        return true;
    }
    else {
        for (const int& nxt : graph[cur]) {
            if (!visit[nxt]) {
                visit[nxt] = true;
                if (dfs(nxt, depth + 1)) {
                    return true;
                }
                visit[nxt] = false;
            }
        }

        return false;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n);
    visit.resize(n);
    for (int i = 0, n1, n2; i < m; i++) {
        cin >> n1 >> n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    /*
    * dfs Å½»öÀÇ ±íÀÌ°¡ 4ÀÌ¸é Å½»ö ³¡.
    */
    bool ans_find = false;
    for (int i = 0; i < n && !ans_find; i++) {
        visit[i] = true;
        ans_find = dfs(i, 0);
        visit[i] = false;
    }

    cout << (ans_find ? 1 : 0);

    return 0;
}