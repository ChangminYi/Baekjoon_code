#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef pair<int, int> pint;

const int INF = INT32_MAX / 2;

int v, e, m, s;
int max_mcdonald, max_starbucks;
vector<list<pint>> graph;
vector<bool> house;
priority_queue<pint, vector<pint>, greater<pint>> pq;

vector<int> dijk(int start) {
    vector<int> dist(v + 3, INF);

    dist[start] = 0;
    pq.push(pint(0, start));
    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const pint& edge : graph[cur]) {
                int nxt = edge.first;
                int new_dist = cur_dist + edge.second;
                int old_dist = dist[nxt];
            
                if (new_dist < old_dist) {
                    dist[nxt] = new_dist;
                    pq.push(pint(new_dist, nxt));
                }
            }
        }
    }

    return dist;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> v >> e;
    graph.resize(v + 3);
    house.resize(v + 3, true);

    int dummy_mc = v + 1, dummy_st = v + 2;
    for (int i = 0, node1, node2, cost; i < e; i++) {
        cin >> node1 >> node2 >> cost;
        graph[node1].push_back(pint(node2, cost));
        graph[node2].push_back(pint(node1, cost));
    }
    house[dummy_mc] = false;
    house[dummy_st] = false;
    cin >> m >> max_mcdonald;
    for (int i = 0, node; i < m; i++) {
        cin >> node;
        house[node] = false;
        graph[dummy_mc].push_back(pint(node, 0));
    }
    cin >> s >> max_starbucks;
    for (int i = 0, node; i < s; i++) {
        cin >> node;
        house[node] = false;
        graph[dummy_st].push_back(pint(node, 0));
    }
    
    /*
    * 그래프 사이즈가 너무 크기 때문에,
    * 집인 노드에 대해서 모두 다익스트라를 실행하면
    * 시간초과가 난다. 그러므로, 더미 노드를 활용한다.
    * 맥도날드와 스타벅스를 모두 잇는 각각의 더미 노드를 생성하여,
    * 그 둘에 대해서만 다익스트라를 실행하면,
    * 매장에서 각각의 집 노드까지의 최단 거리를 얻을 수 있다.
    * 그 후 집 노드에 대해서만 최단 거리를 검사하면 된다.
    */
    int min_dist = INT32_MAX;
    vector<int> dist_mc = dijk(dummy_mc), dist_st = dijk(dummy_st);
    for (int i = 1; i <= v; i++) {
        if (house[i]) {
            if (dist_mc[i] <= max_mcdonald && dist_st[i] <= max_starbucks) {
                min_dist = min(min_dist, dist_mc[i] + dist_st[i]);
            }
        }
    }

    cout << (min_dist == INT32_MAX ? -1 : min_dist);

    return 0;
}