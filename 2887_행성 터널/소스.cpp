#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef struct NODE {
    int x, y, z;
    int idx;
}node;

typedef struct EDGE {
    int i, j, weight;
    bool operator< (const EDGE& comp) const {
        return this->weight < comp.weight;
    }
}edge;

vector<node> graph;
vector<edge> route;
vector<int> parent;

bool comp_x(const node& a, const node& b) {
    return a.x < b.x;
}

bool comp_y(const node& a, const node& b) {
    return a.y < b.y;
}

bool comp_z(const node& a, const node& b) {
    return a.z < b.z;
}

int _find(int x) {
    if (parent[x] == x) {
        return x;
    }
    else {
        return parent[x] = _find(parent[x]);
    }
}

bool is_same_set(int x, int y) {
    return _find(x) == _find(y);
}

void _union(int x, int y) {
    int p_x = _find(x), p_y = _find(y);

    if (p_x < p_y) {
        parent[p_y] = p_x;
    }
    else {
        parent[p_x] = p_y;
    }
}

int get_dist(int i, int j) {
    return abs(i - j);
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);
    
    int n;
    cin >> n;
    
    parent = vector<int>(n);
    graph = vector<node>(n);
    for (int i = 0; i < n; i++) {
        cin >> graph[i].x >> graph[i].y >> graph[i].z;
        graph[i].idx = i;
        parent[i] = i;
    }

    edge tmp;
    int tmp_dist;
    sort(graph.begin(), graph.end(), comp_x);
    for (int i = 0; i < n - 1; i++) {
        tmp_dist = get_dist(graph[i].x, graph[i + 1].x);
        tmp = { graph[i].idx, graph[i + 1].idx, tmp_dist };
        route.push_back(tmp);
    }
    sort(graph.begin(), graph.end(), comp_y);
    for (int i = 0; i < n - 1; i++) {
        tmp_dist = get_dist(graph[i].y, graph[i + 1].y);
        tmp = { graph[i].idx, graph[i + 1].idx, tmp_dist };
        route.push_back(tmp);
    }
    sort(graph.begin(), graph.end(), comp_z);
    for (int i = 0; i < n - 1; i++) {
        tmp_dist = get_dist(graph[i].z, graph[i + 1].z);
        tmp = { graph[i].idx, graph[i + 1].idx, tmp_dist };
        route.push_back(tmp);
    }
    sort(route.begin(), route.end());
    
    long long cost = 0;
    int cnt = 0;
    for (edge& e : route) {
        if (!is_same_set(e.i, e.j)) {
            cost += e.weight;
            _union(e.i, e.j);
            cnt++;

            if (cnt == n - 1) {
                break;
            }
        }
    }

    cout << cost;

    return 0;
}