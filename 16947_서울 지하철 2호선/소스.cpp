#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
int dist[3'001], parent[3'001];
vector<int> graph[3'001];
queue<int> que;
bool flag = false, visit[3'001], in_cycle[3'001];

void bfs() {
    fill(visit + 1, visit + n + 1, false);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const int nxt : graph[cur]) {
            if (!visit[nxt]) {
                visit[nxt] = true;
                dist[nxt] = (in_cycle[nxt] ? 0 : dist[cur] + 1);
                que.push(nxt);
            }
        }
    }
}

void find_cycle(const int cur) {
    visit[cur] = true;
    for (const int nxt : graph[cur]) {
        if (flag) break;
        else {
            if (!visit[nxt]) {
                parent[nxt] = cur;
                find_cycle(nxt);
            }
            else if (nxt != parent[cur]) {
                flag = true;
                in_cycle[cur] = true;
                que.push(cur);
                for (int i = cur; i != nxt; i = parent[i]) {
                    in_cycle[parent[i]] = true;
                }
                break;
            }
            else continue;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ����Ŭ�� ���� ã�ƾ� �ϹǷ�, dfs�� �����Ͽ� ����Ŭ�� ���Ե�
    * �������� ��� ã���ش�. �׸���, �� �� �ƹ� ��带 ť�� �ְ�
    * bfs�� �����ϸ鼭 ����Ŭ�κ����� �Ÿ��� ���ϸ� �ȴ�.
    */

    cin >> n;
    for (int i = 0, n1, n2; i < n; i++) {
        cin >> n1 >> n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    find_cycle(1);
    bfs();

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << ' ';
    }

    return 0;
}