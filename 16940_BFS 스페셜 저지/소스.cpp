#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n;
vector<int> adj[100001];
int seq[100001], real_seq[100001];
int order[100001];
bool visit[100001];
queue<int> que;

bool cmp(const int lhs, const int rhs) {
    return order[lhs] < order[rhs];
}

void bfs() {
    int idx = 1;
    fill(visit + 1, visit + n + 1, false);

    real_seq[0] = 1;
    visit[1] = true;
    que.push(1);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const int nxt : adj[cur]) {
            if (!visit[nxt]) {
                visit[nxt] = true;
                real_seq[idx++] = nxt;
                que.push(nxt);
            }
        }
    }
}

bool is_same_order() {
    for (int i = 0; i < n; i++) {
        if (seq[i] != real_seq[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

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

    /*
    * 탐색이 이뤄진 순서를 기준으로 인접 노드 정렬.
    * 그 후 bfs를 수행하여 실제 순서와 같은지를 판단하면 된다.
    */
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end(), cmp);
    }
    bfs();

    cout << is_same_order() ? 1 : 0;

    return 0;
}