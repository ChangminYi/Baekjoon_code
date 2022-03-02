#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <numeric>
#include <algorithm>

using namespace std;

struct edge {
    int node1, node2, weight;
    edge(const int n1 = 0, const int n2 = 0, const int w = 0) : node1(n1), node2(n2), weight(w) {}
};

int n, m, k;
vector<int> graph[1'001];
int parent[1'001], width[1'001][1'001], min_width[1'001][1'001];
bool visit[1'001];
edge arg[10'000];
queue<int> que;

int find_parent(const int x) {
    if (parent[x] == x) return x;
    else return parent[x] = find_parent(parent[x]);
}

void union_set(const int x, const int y) {
    parent[find_parent(y)] = find_parent(x);
}

void bfs(const int root) {
    fill(visit + 1, visit + n + 1, false);
    fill(min_width[root] + 1, min_width[root] + n + 1, INT32_MAX);
    visit[root] = true;
    for (const int& adj : graph[root]) {
        visit[adj] = true;
        min_width[root][adj] = width[root][adj];
        que.push(adj);
    }

    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const int& nxt : graph[cur]) {
            if (!visit[nxt]) {
                visit[nxt] = true;
                min_width[root][nxt] = min(min_width[root][cur], width[cur][nxt]);
                que.push(nxt);
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 최소 신장 트리 응용. 배의 폭을 최대화하므로, 가장 큰 간선들로 mst를 만든다.
    * 결과물은 최대 신장 트리가 된다. 그 후, 각 노드마다 bfs를 실행하여
    * 해당 노드를 루트 노드로 삼았을 경우의 최소 운하의 폭을 구한다.
    * 그 후, 입력에 따라서 최소 운하의 폭만 출력하면 된다.
    */

    cin >> n >> m >> k;
    iota(parent, parent + n + 1, 0);
    for (int i = 0; i < m; i++) {
        cin >> arg[i].node1 >> arg[i].node2 >> arg[i].weight;
    }

    sort(arg, arg + m, [](const edge& lhs, const edge& rhs) {
        return lhs.weight > rhs.weight;
    });

    for (int i = 0, cnt = 0, fx, fy; i < m && cnt < n - 1; i++) {
        fx = find_parent(arg[i].node1), fy = find_parent(arg[i].node2);
        if (fx != fy) {
            graph[arg[i].node1].push_back(arg[i].node2);
            graph[arg[i].node2].push_back(arg[i].node1);
            width[arg[i].node1][arg[i].node2] = width[arg[i].node2][arg[i].node1] = arg[i].weight;
            cnt++;
            union_set(fx, fy);
        }
    }

    for (int i = 1; i <= n; i++) {
        bfs(i);
    }

    for (int i, j; k; k--) {
        cin >> i >> j;
        cout << min_width[i][j] << '\n';
    }

    return 0;
}