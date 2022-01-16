#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct edge {
    int adj = 0, dist = 0;
    edge() {}
    edge(int _adj, int _dist) : adj(_adj), dist(_dist) {}
};

int n, r, giga, max_dist;
vector<edge> graph[200001];
int dist[200001];
bool visit[200001];

void dfs(const int cur) {
    int child_cnt = 0;

    for (const edge& e : graph[cur]) {
        if (!visit[e.adj]) {
            child_cnt++;
            visit[e.adj] = true;
            dist[e.adj] = dist[cur] + e.dist;
            dfs(e.adj);
        }
    }

    if (child_cnt != 1) {
        giga = cur;
    }
    if (child_cnt == 0) {
        max_dist = max(max_dist, dist[cur]);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ��Ʈ ������ dfs�� Ž��. ���� �ڽ��� ���� 1���� �ƴ϶��, �� ��带 �Ⱑ ���� ����.
    * ��������� ���ƿ��� ������ �Ⱑ ��� ���Ŀ��� ������Ʈ���� ����.
    * �ܸ� ��带 ������ ��, ��Ʈ���������� �ִ� �Ÿ��� ����.
    * �� �� �Ⱑ������ �Ÿ��� ������ ���̸� ���ǿ� �°� ����ϸ� �ȴ�.
    */
    cin >> n >> r;

    fill(visit + 1, visit + n + 1, false);

    for (int i = 0, n1, n2, d; i < n - 1; i++) {
        cin >> n1 >> n2 >> d;
        graph[n1].push_back(edge(n2, d));
        graph[n2].push_back(edge(n1, d));
    }

    visit[r] = true;
    dist[r] = 0;
    dfs(r);

    cout << dist[giga] << ' ' << max_dist - dist[giga];

    return 0;
}