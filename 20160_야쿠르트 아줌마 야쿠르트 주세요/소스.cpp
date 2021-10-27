#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>
#include <algorithm>
#include <map>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
typedef pair<lli, int> pqn;

const lli INF = INT64_MAX / 2;

int v, e, me_start;
vector<int> seq(10);
map<int, lli> arriving;
vector<vector<pint>> graph;
vector<lli> dist;
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk(int start) {
    fill(dist.begin(), dist.end(), INF);

    dist[start] = 0;
    pq.push(pqn(0, start));
    while (!pq.empty()) {
        int cur = pq.top().second;
        lli cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const pint& edge : graph[cur]) {
                int nxt = edge.first;
                int weight = edge.second;

                lli new_dist = cur_dist + weight;
                if (new_dist < dist[nxt]) {
                    dist[nxt] = new_dist;
                    pq.push(pqn(new_dist, nxt));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> v >> e;
    graph.resize(v + 1);
    dist.resize(v + 1);
    for (int i = 0, n1, n2, w; i < e; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }

    /*
    * ����Ʈ ���ܸ��� �̵��� ����Ѵ�.
    * ���� �� �� �ִ��� �� �� �����Ƿ�, map�� ����Ͽ�
    * ��ġ�� ������ش�. ���� �ִ����� ��� �����Ѵ�.
    */
    int cur, prev;
    cin >> cur;
    arriving[cur] = 0;
    prev = cur;
    for (int i = 1; i < 10; i++) {
        cin >> cur;

        dijk(prev);
        if (dist[cur] < INF) {
            arriving[cur] = arriving[prev] + dist[cur];
            prev = cur;
        }
    }

    /*
    * �� ������ġ���� �ִܰŸ� ���ϱ�
    */
    cin >> me_start;
    dijk(me_start);

    /*
    * map�� ������ �� �����̹Ƿ�, ���� ������ �����ϴ� ���� ã����
    * �ٷ� ������ ���������� ����ϸ� �ȴ�.
    */
    int ans = -1;
    for (auto i = arriving.begin(); i != arriving.end(); i++) {
        if (dist[i->first] <= i->second) {
            ans = i->first;
            break;
        }
    }

    cout << ans;

    return 0;
}