#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

int n, m, start, dest;
vector<list<pint>> graph;
vector<bool> visit;

bool bfs(int max_cost) {
    queue<int> que;

    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        if (cur == dest) {
            return true;
        }
        else {
            for (const pint& nxt : graph[cur]) {
                if (!visit[nxt.first] && max_cost <= nxt.second) {
                    visit[nxt.first] = true;
                    que.push(nxt.first);
                }
            }
        }
    }

    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n + 1);
    visit.resize(n + 1);

    int max_weight = 0;
    for (int i = 0, arg1, arg2, arg3; i < m; i++) {
        cin >> arg1 >> arg2 >> arg3;
        graph[arg1].push_back(pint(arg2, arg3));
        graph[arg2].push_back(pint(arg1, arg3));
        max_weight = max(max_weight, arg3);
    }
    cin >> start >> dest;

    /*
    * 최대 중량으로 이분탐색
    * bfs에서 최대중량이 허용되면 lo값을 올리고,
    * 불가라면 hi값을 내린다.
    */
    int lo = 0, hi = max_weight;
    while (lo <= hi) {
        fill(visit.begin(), visit.end(), false);

        int mid = (lo + hi) / 2;
        if (bfs(mid)) {
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    cout << hi;

    return 0;
}