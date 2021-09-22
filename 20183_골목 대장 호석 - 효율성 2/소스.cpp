#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <functional>
#include <algorithm>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, lli> pint;
typedef pair<lli, int> pq_n;

constexpr lli INF = INT64_MAX / 2;

int n, m, a, b;
lli c;
vector<list<pint>> graph;
vector<lli> dist;
vector<int> poss_weight;
priority_queue<pq_n, vector<pq_n>, greater<pq_n>> pq;

bool dijk(lli max_weight) {
    fill(dist.begin(), dist.end(), INF);

    pq.push(pq_n(0, a));
    while (!pq.empty()) {
        int cur = pq.top().second;
        lli cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const pint& nxt : graph[cur]) {
                lli new_dist = cur_dist + nxt.second;
                lli old_dist = dist[nxt.first];

                /*
                * �ܼ� ���ͽ�Ʈ�󿡼� ����
                * ���� ���� ����� ������ weight�� ��� �ִ밪���� ũ��
                * �� ������ ������� ����
                */
                if (new_dist < old_dist && nxt.second <= max_weight) {
                    dist[nxt.first] = new_dist;
                    pq.push(pq_n(new_dist, nxt.first));
                }
            }
        }
    }

    return dist[b] <= c;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> m >> a >> b >> c;
    graph.resize(n + 1);
    dist.resize(n + 1);
    for (int i = 0, arg1, arg2, weight; i < m; i++) {
        cin >> arg1 >> arg2 >> weight;
        graph[arg1].push_back(pint(arg2, weight));
        graph[arg2].push_back(pint(arg1, weight));
        poss_weight.push_back(weight);
    }

    /*
    * ����� �� �ִ� ���� ������ weight�� ���߸� �ȴ�.
    * ��� ���� ���ؼ� �̺�Ž���� �� �ʿ� ����,
    * ������ ������ weight���θ� �̺�Ž���� �����ϸ� �ȴ�.
    */
    sort(poss_weight.begin(), poss_weight.end());
    poss_weight.erase(unique(poss_weight.begin(), poss_weight.end()), poss_weight.end());

    /*
    * ���ĵ� ������ ����ġ�� ���ؼ� �̺�Ž��
    * mid���� ���ؼ� �湮�� �����ϸ� hi�� ���� �ּڰ��� ���ϰ�,
    * �Ұ����ϸ� lo�� �÷� ������ ������ ã��
    * ���� �湮�� �����ϸ�(hi �ֽ�ȭ) ���� �ĺ� �� �ϳ��̹Ƿ� ans �ֽ�ȭ
    */
    int lo = 0, hi = poss_weight.size() - 1;
    int ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        if (dijk(poss_weight[mid])) {
            hi = mid - 1;
            ans = poss_weight[mid];
        }
        else {
            lo = mid + 1;
        }
    }

    cout << ans;

    return 0;
}