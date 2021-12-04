#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;

const int INF = INT32_MAX;

int testcase;

void dijk() {
    int n, m;
    cin >> n >> m;

    vector<vector<pint>> graph(m);
    vector<int> dist(m, INF);
    vector<int> parent(m);

    for (int i = 0, n1, n2, w; i < n; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }

    priority_queue<pint, vector<pint>, greater<pint>> pq;
    parent[0] = 0;
    dist[0] = 0;
    pq.push(pint(dist[0], 0));
    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const pint& edge : graph[cur]) {
                int new_dist = cur_dist + edge.second;

                if (new_dist < dist[edge.first]) {
                    dist[edge.first] = new_dist;
                    parent[edge.first] = cur;
                    pq.push(pint(new_dist, edge.first));
                }
            }
        }
    }

    if (dist[m - 1] == INF) {
        cout << -1;
    }
    else {
        stack<int> stk;
        stk.push(m - 1);
        while (parent[stk.top()] != stk.top()) {
            stk.push(parent[stk.top()]);
        }

        while (!stk.empty()) {
            cout << stk.top() << ' ';
            stk.pop();
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 다익스트라 알고리즘을 사용하여 최단경로 역추적을 하면 된다.
    */
    cin >> testcase;
    for (int i = 1; i <= testcase; i++) {
        cout << "Case #" << i << ": ";
        dijk();
    }

    return 0;
}