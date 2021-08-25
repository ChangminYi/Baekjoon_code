#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
typedef pair<lli, lli> plli;

const lli INF = INT64_MAX / 2;

int n, m, k;
int depart, arrive;
vector<pint> edge(2020);
vector<vector<int>> weight(111, vector<int>(2020));
vector<vector<plli>> graph(303030);
vector<lli> dist(303030);

int id(int a, int b) {
    return a * 2020 + b;
}

lli dijk() {
    fill(dist.begin(), dist.end(), INF);
    priority_queue<plli, vector<plli>, greater<plli>> pq;
    
    dist[id(0, depart)] = 0;
    pq.push(make_pair(0, id(0, depart)));

    while (!pq.empty()) {
        lli cur = pq.top().second;
        lli cst = pq.top().first;
        pq.pop();

        if (cst <= dist[cur]) {
            for (const plli &edge : graph[cur]) {
                lli new_dist = cst + edge.second;
                lli old_dist = dist[edge.first];

                if (new_dist < old_dist) {
                    dist[edge.first] = new_dist;
                    pq.push(make_pair(dist[edge.first], edge.first));
                }
            }
        }
    }

    lli min_dist = INF;
    for (int i = 0; i <= k; i++) {
        min_dist = min(min_dist, dist[id(i, arrive)]);
    }

    return min_dist;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> depart >> arrive;
    for (int i = 1; i <= m; i++) {
        cin >> edge[i].first >> edge[i].second >> weight[0][i];
    }
    cin >> k;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> weight[i][j];
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= k; j++) {
            graph[id(j, edge[i].first)].push_back(make_pair(id(j, edge[i].second), weight[j][i]));
            graph[id(j, edge[i].second)].push_back(make_pair(id(j, edge[i].first), weight[j][i]));
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            graph[id(j, i)].push_back(make_pair(id(j + 1, i), 0));
        }
    }

    cout << dijk();

    return 0;
}