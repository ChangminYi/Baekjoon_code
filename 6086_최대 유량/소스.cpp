#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <limits>
#include <cctype>

using namespace std;

const int NOT_VISIT = -1;
const int MAX_SIZE = 52;
const int start = 0;
const int last = 25;

int n;
int max_flow[MAX_SIZE][MAX_SIZE] = { 0 };
int cur_flow[MAX_SIZE][MAX_SIZE] = { 0 };
vector<list<int>> graph(MAX_SIZE);
vector<int> parent(MAX_SIZE);
queue<int> que;

int c_to_i(char c) {
    return (isupper(c) ? c - 'A' : c - 'a' + 26);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;

    for (int i = 0, node1, node2; i < n; i++) {
        char c1, c2; int w;

        cin >> c1 >> c2 >> w;

        node1 = c_to_i(c1), node2 = c_to_i(c2);
        max_flow[node1][node2] = max_flow[node2][node1] += w;
        graph[node1].push_back(node2);
        graph[node2].push_back(node1);
    }

    int total_flow = 0;
    while (true) {
        fill(parent.begin(), parent.end(), NOT_VISIT);
        while (!que.empty()) {
            que.pop();
        }

        que.push(start);
        while (!que.empty() && parent[last] == NOT_VISIT) {
            int cur = que.front();
            que.pop();

            for (const int& nxt : graph[cur]) {
                if (max_flow[cur][nxt] > cur_flow[cur][nxt] && parent[nxt] == NOT_VISIT) {
                    que.push(nxt);
                    parent[nxt] = cur;
                    
                    if (nxt == last) {
                        break;
                    }
                }
            }
        }

        if (parent[last] == NOT_VISIT) {
            break;
        }
        else {
            int tmp_flow = INT32_MAX;

            for (int i = last; i != start; i = parent[i]) {
                tmp_flow = min(tmp_flow, max_flow[parent[i]][i] - cur_flow[parent[i]][i]);
            }
            for (int i = last; i != start; i = parent[i]) {
                cur_flow[parent[i]][i] += tmp_flow;
                cur_flow[i][parent[i]] -= tmp_flow;
            }

            total_flow += tmp_flow;
        }
    }
    
    cout << total_flow;

    return 0;
}