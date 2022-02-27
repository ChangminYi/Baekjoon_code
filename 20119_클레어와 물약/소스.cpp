#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

int n, m, l;
int buf[200'000];
bool visit[200'001];
vector<int> degree[200'001];
vector<pint> graph[200'001];
queue<int> que;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �� ������ ����� ����� ���� �� ������ �� �ִ�.
    * ����, ��� �����Ǹ� �����ϱ� ���ؼ� degree�� 2�������� �����ϰ�,
    * �׷����� ������ ��� ��ȣ�� degree�� �ε����� �����Ѵ�.
    * ���� ������ ������ ���� ��� ��ȣ���� ����Ͽ� �����ϸ� �ȴ�.
    */

    cin >> n >> m;
    for (int k, r; m; m--) {
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> buf[i];
        }
        cin >> r;
        degree[r].push_back(k);
        for (int i = 0; i < k; i++) {
            graph[buf[i]].push_back(pint(r, degree[r].size() - 1));
        }
    }
    cin >> l;
    for (int i = 0, tmp; i < l; i++) {
        cin >> tmp;
        que.push(tmp);
        visit[tmp] = true;
    }

    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const pint& edge : graph[cur]) {
            if (--degree[edge.first][edge.second] == 0 && !visit[edge.first]) {
                visit[edge.first] = true;
                l++;
                que.push(edge.first);
            }
        }
    }

    cout << l << '\n';
    for (int i = 1; i <= n; i++) {
        if (visit[i]) cout << i << ' ';
    }

    return 0;
}