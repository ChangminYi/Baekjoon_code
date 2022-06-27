#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct edge {
    int n1, n2, weight;
    edge(const int _n1 = 0, const int _n2 = 0, const int _w = 0) : n1(_n1), n2(_n2), weight(_w) {}
    bool operator<(const edge& other) {
        return weight < other.weight;
    }
};

int n, edge_cnt;
int parent[1025];
vector<int> adj[1025];
edge arg[523776];

int find_par(const int x) {
    if(parent[x] == x) return x;
    else return parent[x] = find_par(parent[x]);
}

void union_set(const int x, const int y) {
    parent[find_par(x)] = find_par(y);
}

int main() {
    /**
     * 인접 행렬의 값 중에는 두 노드를 직접 잇는 간선이 모두 포함되어 있다.
     * 따라서, 최소 스패닝 트리를 만들면 원래 트리가 복원된다.
     * 간선 정보를 저장하고, 노드 번호 순으로 정렬하여 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    iota(parent + 1, parent + n + 1, 1);
    for(int i = 1, val; i <= n - 1; i++) {
        for(int j = i + 1; j <= n; j++) {
            cin >> val;
            arg[edge_cnt].n1 = i, arg[edge_cnt].n2 = j, arg[edge_cnt].weight = val;
            edge_cnt++;
        }
    }

    sort(arg, arg + edge_cnt);

    for(int i = 0, cnt = 0; i < edge_cnt && cnt < n - 1; i++) {
        if(find_par(arg[i].n1) != find_par(arg[i].n2)) {
            adj[arg[i].n1].push_back(arg[i].n2);
            adj[arg[i].n2].push_back(arg[i].n1);
            union_set(arg[i].n1, arg[i].n2);
            cnt++;
        }
    }

    for(int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
        cout << adj[i].size() << ' ';
        for(const int& n: adj[i]) {
            cout << n << ' ';
        }
        cout << '\n';
    }

    return 0;
}