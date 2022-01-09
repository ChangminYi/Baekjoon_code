#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct pqn {
    int dist = 0, node = 0;
    pqn(int _n, int _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const {
        return this->dist > other.dist;
    }
};

const int INF = INT32_MAX / 2;
const int START = 1;
const int END = 2;

int n, m;
vector<int> graph[1001];
int weight[1001][1001];
int dist[1001], dp[1001];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk() {
    fill(dist + 1, dist + n + 1, INF);

    dist[END] = 0;
    dp[END] = 1;
    pq.push(pqn(END, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const int prev : graph[cur]) {
                int new_dist = cur_dist + weight[cur][prev];

                if (new_dist < dist[prev]) {
                    dist[prev] = new_dist;
                    pq.push(pqn(prev, new_dist));
                }
                if (cur_dist > dist[prev]) {
                    dp[cur] += dp[prev];
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���ͽ�Ʈ�� �˰����� ���� END���� �ִܰŸ��� ���ϴ� ���ÿ�
    * dp �迭�� ������Ʈ. ���� ���� �Ÿ��� ����� ��庸�� ũ�ٸ�, 
    * ����� ��忡�� ���� ��ġ���� �̵��� �ո����� �̵�.
    * ���� �� �� �ִ� ����� ���� �����ְ�, dp[START]�� ����ϸ� �ȴ�.
    */
    cin >> n >> m;
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
        weight[n1][n2] = weight[n2][n1] = w;
    }

    dijk();
    cout << dp[START];

    return 0;
}