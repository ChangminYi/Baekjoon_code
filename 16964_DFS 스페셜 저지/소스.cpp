#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, idx = 0;
vector<int> adj[100001];
int seq[100001], order[100001], real_visit[100001];
bool visit[100001];

bool cmp(const int lhs, const int rhs) {
    return order[lhs] < order[rhs];
}

void dfs(const int cur) {
    for (const int nxt : adj[cur]) {
        if (!visit[nxt]) {
            visit[nxt] = true;
            real_visit[idx++] = nxt;
            dfs(nxt);
        }
    }
}

bool has_same_order() {
    for (int i = 0; i < n; i++) {
        if (seq[i] != real_visit[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * dfs를 실행하지만, 방문하는 노드의 순서가 정해져있음.
    * 예상 방문 순서를 통해 인접 노드를 모두 정렬하고,
    * 그 순서대로 dfs를 실행하여 실제 방문 순서와 일치하는지를 체크.
    */
    cin >> n;
    for (int i = 0, n1, n2; i < n - 1; i++) {
        cin >> n1 >> n2;
        adj[n1].push_back(n2);
        adj[n2].push_back(n1);
    }
    for (int i = 0; i < n; i++) {
        cin >> seq[i];
        order[seq[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end(), cmp);
    }

    fill(visit + 1, visit + n + 1, false);
    visit[1] = true;
    real_visit[idx++] = 1;
    dfs(1);
    cout << has_same_order() ? 1 : 0;

    return 0;
}