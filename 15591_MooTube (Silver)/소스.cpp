#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int usado, node;
    edge(const int _n = 0, const int _u = 0) : node(_n), usado(_u) {}
};

int n, q;
int usado[5'001];
bool visit[5'001];
vector<edge> tree[5'001];
queue<int> que;

int bfs(const int start, const int base) {
    int ret = 0;
    fill(visit + 1, visit + n + 1, false);

    visit[start] = true;
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const edge& e : tree[cur]) {
            if (!visit[e.node] && e.usado >= base) {
                visit[e.node] = true;
                ret++;
                que.push(e.node);
            }
        }
    }

    return ret;
}

int main() {
    /*
    * 네트워크가 트리 형태이기 때문에, 단순 bfs로 해결 가능하다.
    * 간선의 usado가 k 미만이면 그 경로에서의 탐색을 중단한다.
    * 시작점을 제외한, bfs로 방문한 노드의 수를 출력하면 된다.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> q;
    for (int i = 0, p, q, r; i < n - 1; i++) {
        cin >> p >> q >> r;
        tree[p].push_back(edge(q, r));
        tree[q].push_back(edge(p, r));
    }

    for (int k, v; q; q--) {
        cin >> k >> v;
        cout << bfs(v, k) << '\n';
    }

    return 0;
}