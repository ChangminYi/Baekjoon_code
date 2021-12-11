#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<vector<int>> h_graph, l_graph;
vector<bool> h_visit, l_visit;

int dfs(const int cur, const bool is_heavy) {
    vector<vector<int>>& graph = (is_heavy ? h_graph : l_graph);
    vector<bool>& visit = (is_heavy ?  h_visit : l_visit);
    int ret = 1;

    for (const int& nxt : graph[cur]) {
        if (!visit[nxt]) {
            visit[nxt] = true;
            ret += dfs(nxt, is_heavy);
        }
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    h_graph.resize(n + 1), l_graph.resize(n + 1);
    h_visit.resize(n + 1), l_visit.resize(n + 1);

    for (int i = 0, heavy, light; i < m; i++) {
        cin >> heavy >> light;
        l_graph[heavy].push_back(light);
        h_graph[light].push_back(heavy);
    }

    /*
    * 자신보다 무겁거나 가벼운 원소가 전체 원소의 절반 이상이면
    * 해당 무게는 중간이 될 수 없음.
    */
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        fill(h_visit.begin(), h_visit.end(), false);
        fill(l_visit.begin(), l_visit.end(), false);

        h_visit[i] = true, l_visit[i] = true;
        if (dfs(i, true) > (n + 1) / 2 || dfs(i, false) > (n + 1) / 2) {
            cnt++;
        }
    }

    cout << cnt;

    return 0;
}