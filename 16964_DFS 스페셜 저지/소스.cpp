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
    * dfs�� ����������, �湮�ϴ� ����� ������ ����������.
    * ���� �湮 ������ ���� ���� ��带 ��� �����ϰ�,
    * �� ������� dfs�� �����Ͽ� ���� �湮 ������ ��ġ�ϴ����� üũ.
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