#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct edge {
    int node, weight;
    edge(int _n = 0, int _w = 0) : node(_n), weight(_w) {}
};

int n, m, s, e;
int lo = 1, hi = 0, ans = 0;
vector<edge> graph[100'001];
bool visit[100'001];

bool bfs(const int cur_weight) {
    queue<int> que;

    fill(visit + 1, visit + n + 1, false);
    visit[s] = true;
    que.push(s);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        if (cur == e) {
            return true;
        }
        else {
            for (const edge& e : graph[cur]) {
                if (!visit[e.node] && cur_weight <= e.weight) {
                    visit[e.node] = true;
                    que.push(e.node);
                }
            }
        }
    }

    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 가지고 갈 수 있는 금빼빼로의 무게를 매개로 이분탐색을 진행.
    * bfs를 진행할 때 방문하지 않았고, 무게가 허용치보다 낮다면 다음 노드 탐색.
    * 최솟값은 허용 최소치인 1, 최댓값은 간선의 최대 허용량.
    */

    cin >> n >> m >> s >> e;
    for (int h1, h2, k; m; m--) {
        cin >> h1 >> h2 >> k;
        graph[h1].push_back(edge(h2, k));
        graph[h2].push_back(edge(h1, k));
        hi = max(hi, k);
    }

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (bfs(mid)) {
            ans = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    cout << ans;

    return 0;
}