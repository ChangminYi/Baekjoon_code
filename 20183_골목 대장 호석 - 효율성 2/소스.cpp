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
                * 단순 다익스트라에서 변형
                * 다음 노드로 연결된 간선이 weight의 허용 최대값보다 크면
                * 그 간선을 사용하지 못함
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
    * 사용할 수 있는 돈은 간선의 weight에 맞추면 된다.
    * 모든 값에 대해서 이분탐색을 할 필요 없이,
    * 등장한 간선의 weight으로만 이분탐색을 진행하면 된다.
    */
    sort(poss_weight.begin(), poss_weight.end());
    poss_weight.erase(unique(poss_weight.begin(), poss_weight.end()), poss_weight.end());

    /*
    * 정렬된 간선의 가중치에 대해서 이분탐색
    * mid값에 대해서 방문이 가능하면 hi를 낮춰 최솟값을 구하고,
    * 불가능하면 lo를 올려 가능한 범위를 찾음
    * 만약 방문이 가능하면(hi 최신화) 정답 후보 중 하나이므로 ans 최신화
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