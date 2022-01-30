#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct pqn {
    int node, dist;
    pqn(const int _n = 0, const int _d = 0) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const { return this->dist > other.dist; }
};

const int INF = INT32_MAX / 2;

int n, m;
vector<int> graph[501];
int dist[501][501];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk(const int start) {
    fill(dist[start] + 1, dist[start] + n + 1, INF);
    dist[start][start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (const int nxt : graph[cur]) {
                int new_dist = cur_dist + 1;
                if (new_dist < dist[start][nxt]) {
                    dist[start][nxt] = new_dist;
                    pq.push(pqn(nxt, new_dist));
                }
            }
        }
    }
}

bool can_know_all(const int cur) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i != cur) {
            if (dist[i][cur] != INF || dist[cur][i] != INF) {
                cnt++;
            }
        }
    }
    return cnt == n - 1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ��� ���� Ű�� �� ���� ������ �ִ� �������� ����Ѵ�.
    * ������ ����ġ�� ������ ����Ͽ� 1�� ����.
    * �÷��̵�-�ͼ��̳� ���ͽ�Ʈ�� ���� ��ü ��忡 ���� ��ü �Ÿ��� ���ϰ�,
    * ������ ��忡 ���ؼ� �ڽ��� �����ϰ�, �Ÿ��� ���Ѵ밡 �ƴ� ��带 ã�´�.
    * �ڽ��� ��Ȯ�� ������ �ƴ� ����, ��� ����� ���ؼ� �̵� �����ϴٴ� ��.
    * ���� ī��Ʈ�� n-1���̸� �ڽ��� ��Ȯ�� ������ �� �� �ִ� ���̴�.
    */
    cin >> n >> m;
    for (int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
    }

    for (int i = 1; i <= n; i++) {
        dijk(i);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (can_know_all(i)) ans++;
    }

    cout << ans;

    return 0;
}