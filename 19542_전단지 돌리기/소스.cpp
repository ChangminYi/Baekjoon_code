#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, s, d;
long long visit_cnt = 1;
vector<int> adj[100'001];
int depth_reverse[100'001], visit[100'001];

int init_depth(const int cur) {
    depth_reverse[cur] = 0;
    for (const int& nxt : adj[cur]) {
        if (!visit[nxt]) {
            visit[nxt] = true;
            depth_reverse[cur] = max(depth_reverse[cur], init_depth(nxt));
        }
    }
    return depth_reverse[cur] + 1;
}

void dfs(const int cur) {
    for (const int& nxt : adj[cur]) {
        if (!visit[nxt] && depth_reverse[nxt] >= d) {
            visit_cnt++;
            visit[nxt] = true;
            dfs(nxt);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * dfs를 2번 반복하여 결과를 구할 수 있다.
    * 첫 번째 dfs에서는 트리를 구축하고, 단말 노드부터 깊이를 매긴다.
    * 두 번째 dfs에서는 조건에 따라 트리를 순회하고, 방문한 노드의 수를 저장한다.
    * 2 * (방문한 노드 수 - 1)이 이동한 거리가 된다.
    */
    cin >> n >> s >> d;
    for (int i = 0, n1, n2; i < n - 1; i++) {
        cin >> n1 >> n2;
        adj[n1].push_back(n2), adj[n2].push_back(n1);
    }

    visit[s] = true;
    init_depth(s);

    fill(visit + 1, visit + n + 1, false);
    visit[s] = true;
    dfs(s);

    cout << 2 * (visit_cnt - 1);

    return 0;
}