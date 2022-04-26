#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int NOT_VISIT = -1;

int n;
vector<int> tree[10'001];
int weight[10'001], dist[10'001];
queue<int> que;

pair<int, int> bfs(const int start) {
    int idx = 0, max_val = -1;

    fill(dist+ 1, dist + n + 1, NOT_VISIT);
    dist[start] = weight[start];
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        if (dist[cur] > max_val || (dist[cur] == max_val && cur < idx)) {
            idx = cur;
            max_val = dist[cur];
        }

        for (const int nxt : tree[cur]) {
            if (dist[nxt] == NOT_VISIT) {
                dist[nxt] = dist[cur] + weight[nxt];
                que.push(nxt);
            }
        }
    }

    return pair<int, int>(idx, max_val);
}

int main() {
    /*
    * 트리의 지름 응용. 단순히 거리가 아니라, 노드의 가중치의 합의 최대를 구한다.
    * 트리 형태이므로, 단순 bfs을 통해 전체를 탐색할 수 있다.
    * 노드 번호가 가장 작은 것을 출력해야 하므로, 두 번의 탐색 결과를 모두
    * 저장하여 그 중 노드 번호가 작은 것을 출력하면 된다.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> weight[i];
    }
    for (int i = 0, a, b; i < n - 1; i++) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    pair<int, int> res1 = bfs(1);
    pair<int, int> res2 = bfs(res1.first);

    cout << res2.second << ' ' << min(res1.first, res2.first);

    return 0;
}