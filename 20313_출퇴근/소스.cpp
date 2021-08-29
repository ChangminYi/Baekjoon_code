#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef long long lli;
struct edge {
    int node1, node2;
    int weight;
    edge(int n1 = 0, int n2 = 0, int w = 0) : node1(n1), node2(n2), weight(w) {}
};
struct pq_node {
    int node_num;
    lli dist;
    pq_node(int n = 0, lli d = 0) : node_num(n), dist(d) {}
};
typedef pair<int, int> pint;

const lli INF = INT64_MAX / 2;

int n, m, k;
int depart, arrive;
vector<edge> all_edge;
vector<vector<pint>> graph;
vector<lli> dist;

bool operator>(const pq_node& a, const pq_node& b) {
    return a.dist > b.dist;
}

lli dijk() {
    dist.resize(graph.size(), INF);
    priority_queue<pq_node, vector<pq_node>, greater<pq_node>> pq;

    dist[depart] = 0;
    pq.push(pq_node(depart, dist[depart]));

    while (!pq.empty()) {
        pq_node cur = pq.top();
        pq.pop();

        if (cur.dist <= dist[cur.node_num]) {
            for (const pint& e : graph[cur.node_num]) {
                lli new_dist = cur.dist + e.second;
                lli old_dist = dist[e.first];

                if (new_dist < old_dist) {
                    dist[e.first] = new_dist;
                    pq.push(pq_node(e.first, new_dist));
                }
            }
        }
    }

    lli min_dist = INF;
    for (int i = 0; i <= k; i++) {
        min_dist = min(min_dist, dist[arrive + i * n]);
    }

    return min_dist;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> depart >> arrive;
    all_edge.resize(m);
    for (edge& e : all_edge) {
        cin >> e.node1 >> e.node2 >> e.weight;
    }
    cin >> k;
    all_edge.resize(m * (k + 1));
    for (int i = m; i < (int)all_edge.size(); i++) {
        all_edge[i].node1 = all_edge[i - m].node1 + n;
        all_edge[i].node2 = all_edge[i - m].node2 + n;
        cin >> all_edge[i].weight;
    }

    graph.resize(n * (k + 1) + 1);
    for (edge& e : all_edge) {
        graph[e.node1].push_back(make_pair(e.node2, e.weight));
        graph[e.node2].push_back(make_pair(e.node1, e.weight));
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            graph[i + (j - 1) * n].push_back(make_pair(i + j * n, 0));
        }
    }

    cout << dijk();

    return 0;
}