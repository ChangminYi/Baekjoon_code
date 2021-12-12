#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
typedef pair<int, int> pint;

int n, r1, r2;
vector<vector<pint>> graph;
vector<int> dist, parent;
vector<bool> visit;

void bfs(const int start) {
    queue<int> que;

    parent[start] = start;
    dist[start] = 0;
    visit[start] = true;
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const pint& edge : graph[cur]) {
            if (!visit[edge.first]) {
                visit[edge.first] = true;
                dist[edge.first] = dist[cur] + edge.second;
                parent[edge.first] = cur;
                que.push(edge.first);
            }
        }
    }
}

int get_max_weight() {
    int ret = 0;
    int cur = r2;
    while (parent[cur] != cur) {
        ret = max(ret, dist[cur] - dist[parent[cur]]);
        cur = parent[cur];
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> r1 >> r2;
    graph.resize(n + 1);
    dist.resize(n + 1);
    parent.resize(n + 1);
    visit.resize(n + 1, false);

    /*
    * ���� ������ �̿��� ��� �� �κ��� ��ġ�κ����� ��� ������
    * �ִܰŸ��� ���Ѵ�. �׿� ���ÿ� parent�� �̿��� �������� �����ϰ�
    * ���. �� ��° �κ����� ù ��° �κ������� ��� �� ���� �� ���̸�
    * ������ ������ ���̸� ���ϰ�, ��ü ���̿��� �� ���� ���� ��.
    */
    for (int i = 0, n1, n2, w; i < n - 1; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }

    bfs(r1);

    cout << dist[r2] - get_max_weight();

    return 0;
}