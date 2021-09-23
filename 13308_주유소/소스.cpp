#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
struct pq_n {
    int node = 0, cost;
    lli dist = 0;
    pq_n(int n, lli c, lli d) : node(n), cost(c), dist(d) {}
    bool operator>(const pq_n& rhs) const{
        return this->dist > rhs.dist;
    }
};

constexpr int MAX_COST = 2501;

int n, m;
vector<vector<pint>> graph;
vector<int> gas_cost;
vector<vector<bool>> visit;
priority_queue<pq_n, vector<pq_n>, greater<pq_n>> pq;

/*
* dp이지만, 다익스트라의 성질을 이용하여 테이블 만들지 않을 수 있음.
* pq에서는 언제나 최솟값이 나온다.
* 만약 테이블이 있다고 가정하면, dp[node][min_cost] = cur_cost * weight + cur_dist
* 다익스트라를 돌리다가 처음으로 노드가 n인 경우, 그 때의 dist가 최소비용
* 기름값이 가장 적은 노드에서 최대한 기름을 많이 넣게 된다.
* 그래서 min_cost = min(cur.cost, gas_cost[nxt])가 된다.
*/
lli dijk() {
    pq.push(pq_n(1, gas_cost[1], 0));

    while (!pq.empty()) {
        pq_n cur = pq.top();
        pq.pop();

        if (cur.node == n) {
            return cur.dist;
        }
        else {
            if (!visit[cur.node][cur.cost]) {
                visit[cur.node][cur.cost] = true;

                for (const pint& nxt : graph[cur.node]) {
                    lli min_cost = min<lli>(cur.cost, gas_cost[nxt.first]);
                    lli new_dist = (lli)cur.cost * nxt.second + cur.dist;

                    pq.push(pq_n(nxt.first, min_cost, new_dist));
                }
            }
        }
    }

    return 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n + 1);
    gas_cost.resize(n + 1);
    visit.resize(n + 1, vector<bool>(MAX_COST, false));
    for (int i = 1; i <= n; i++) {
        cin >> gas_cost[i];
    }
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }

    cout << dijk();

    return 0;
}