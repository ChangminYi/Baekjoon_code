#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m, ans;
vector<int> graph[100'001];
int degree[100'001];
queue<int> que;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� �׷�������, ����Ŭ�� ������ �� ���� ��带 ���� ���� �Ѵ�.
    * �׷����� ������ ��� ������ ������ �� ���� ������ �Ѵ�.
    * ���Ŀ� ������ ����� ���� ���� �׷������� ����Ŭ�� ������ �� ���� ����� ���� ����.
    * ������ �׷������� �湮�� �� ���� ������ ��� ����Ŭ�� ���Ե� ����.
    */

    cin >> n >> m;
    for (int u, v; m; m--) {
        cin >> v >> u;
        graph[u].push_back(v);
        degree[v]++;
    }

    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) {
            ans++;
            que.push(i);
        }
    }
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const int& nxt : graph[cur]) {
            if (--degree[nxt] == 0) {
                ans++;
                que.push(nxt);
            }
        }
    }

    cout << ans;

    return 0;
}