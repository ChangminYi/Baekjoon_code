#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef pair<int, double> edge;
typedef pair<double, int> pq_n;
constexpr double INF = INT64_MAX / 2;

int n, m, k, r;
vector<int> to_visit;
vector<double> dist;
vector<list<edge>> graph, dc_graph;
unordered_map<string, int> city_idx;
unordered_set<string> pass_100 = { "Mugunghwa", "ITX-Saemaeul", "ITX-Cheongchun" };
unordered_set<string> pass_50 = { "S-Train", "V-Train" };
priority_queue<pq_n, vector<pq_n>, greater<pq_n>> pq;

double dijk(int start, int dest, vector<list<edge>>& grp) {
    fill(dist.begin(), dist.end(), INF);

    dist[start] = 0;
    pq.push(pq_n(0, start));
    while (!pq.empty()) {
        double cur_dist = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const edge& e : grp[cur]) {
                int nxt = e.first;
                double nxt_weight = e.second;

                double new_dist = cur_dist + nxt_weight;
                double old_dist = dist[nxt];
                if (new_dist < old_dist) {
                    dist[nxt] = new_dist;
                    pq.push(pq_n(new_dist, nxt));
                }
            }
        }
    }

    return dist[dest];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    (cin >> n >> r).ignore();
    for (int i = 0, cnt = 0; i < n; i++) {
        string tmp;
        cin >> tmp;
        if (city_idx.find(tmp) == city_idx.end()) {
            city_idx.insert(make_pair(tmp, cnt++));
        }
    }
    graph.resize(city_idx.size());
    dc_graph.resize(city_idx.size());
    (cin >> m).ignore();
    to_visit.resize(m);
    for (int i = 0; i < m; i++) {
        string tmp;
        cin >> tmp;
        to_visit[i] = city_idx[tmp];
    }
    (cin >> k).ignore();
    for (int i = 0; i < k; i++) {
        string ve, node1, node2;
        /*
        * 자료형 함정...? int에서 double로 바꾸니 맞았음
        */
        double weight;

        (cin >> ve >> node1 >> node2 >> weight).ignore();

        graph[city_idx[node1]].push_back(edge(city_idx[node2], weight));
        graph[city_idx[node2]].push_back(edge(city_idx[node1], weight));
        if (pass_100.find(ve) != pass_100.end()) {
            dc_graph[city_idx[node1]].push_back(edge(city_idx[node2], 0));
            dc_graph[city_idx[node2]].push_back(edge(city_idx[node1], 0));
        }
        else if (pass_50.find(ve) != pass_50.end()) {
            dc_graph[city_idx[node1]].push_back(edge(city_idx[node2], weight / 2));
            dc_graph[city_idx[node2]].push_back(edge(city_idx[node1], weight / 2));
        }
        else {
            dc_graph[city_idx[node1]].push_back(edge(city_idx[node2], weight));
            dc_graph[city_idx[node2]].push_back(edge(city_idx[node1], weight));
        }
    }
    dist.resize(city_idx.size());

    /*
    * 할인된 그래프와 일반 그래프 두 개를 만들어서
    * 계속 다익스트라를 돌려 거리 계산 후 업데이트
    * 그리고 조건에 맞게 출력
    */
    double cost = 0, dc_cost = r;
    for (int i = 0; i < m - 1; i++) {
        cost += dijk(to_visit[i], to_visit[i + 1], graph);
        dc_cost += dijk(to_visit[i], to_visit[i + 1], dc_graph);
    }

    cout << (dc_cost < cost ? "Yes" : "No");

    return 0;
}