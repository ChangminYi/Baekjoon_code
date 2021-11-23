#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

const int MAX = 100001;
const int MAX_COL = 17;

int n;
vector<vector<pint>> graph;
vector<vector<int>> parent;
vector<int> energy, dist;

void dfs(int cur, int prev) {
    for (const pint& nxt : graph[cur]) {
        if (nxt.first != prev) {
            dist[nxt.first] = dist[cur] + nxt.second;
            parent[nxt.first][0] = cur;

            dfs(nxt.first, cur);
        }
    }
}

void init_parent() {
    for (int j = 1; j < MAX_COL; j++) {
        for (int i = 1; i <= n; i++) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }
}

int get_max_num(int i) {
    int remain_energy = energy[i];

    for (int j = MAX_COL - 1; j >= 0; j--) {
        if (dist[i] - dist[parent[i][j]] <= remain_energy) {
            remain_energy -= dist[i] - dist[parent[i][j]];
            i = parent[i][j];
        }
    }

    return i;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    energy.resize(n + 1);
    dist.resize(n + 1);
    graph.resize(n + 1);
    parent.resize(n + 1, vector<int>(MAX_COL));

    for (int i = 1; i <= n; i++) {
        cin >> energy[i];
    }
    for (int i = 0, n1, n2, weight; i < n - 1; i++) {
        cin >> n1 >> n2 >> weight;
        graph[n1].push_back(pint(n2, weight));
        graph[n2].push_back(pint(n1, weight));
    }

    // 트리 초기화
    parent[1][0] = 1;
    dist[1] = 0;
    dfs(1, 0);

    // 부모 배열 초기화
    init_parent();

    /*
    * 한 단계씩 올라가는 것이 아닌, 2의 승만큼 건너뛰어 올라간다.
    * 만약 현재 남은 에너지보다 작은 2^j승의 부모까지의 거리가 발견된다면,
    * 바로 2^j승의 부모로 바로 건너뛴다.
    */
    for (int i = 1; i <= n; i++) {
        cout << get_max_num(i) << '\n';
    }

    return 0;
}