#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

bool bfs(map<int, vector<int>>& graph) {
    map<int, bool> visit;

    for (auto t : graph) {
        for (const int& n : t.second) {
            visit[n] = true;
        }
    }

    int root = 0;
    for (auto t : graph) {
        if (!visit[t.first]) {
            root = t.first;
        }
    }

    visit.clear();
    visit[root] = true;
    queue<int> que;
    que.push(root);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const int& nxt: graph[cur]) {
            if (visit[nxt]) {
                return false;
            }
            else {
                visit[nxt] = true;
                que.push(nxt);
            }
        }
    }

    for (auto t : graph) {
        for (const int& n : t.second) {
            if (!visit[n] || !visit[t.first]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    for (int testcase = 1; ; testcase++) {
        int e_cnt = 0;
        map<int, vector<int>> graph;
        set<int> node;
        int u, v;
        
        while (true) {
            cin >> u >> v;
            e_cnt++;
            node.insert(u), node.insert(v);
            
            if (u == -1 && v == -1) {
                return 0;
            }
            else if (u == 0 && v == 0) {
                break;
            }
            else {
                graph[u].push_back(v);
            }
        }

        if (u > 0 && v > 0 && e_cnt != node.size() - 1) {
            printf("Case %d is not a tree.\n", testcase);
        }
        else {
            if (bfs(graph)) {
                printf("Case %d is a tree.\n", testcase);
            }
            else {
                printf("Case %d is not a tree.\n", testcase);
            }
        }
    }

    return 0;
}