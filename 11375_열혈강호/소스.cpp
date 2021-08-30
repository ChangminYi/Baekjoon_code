#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int NOT_MATCH = 0;

int n, m;
vector<list<int>> graph;
vector<int> match;
vector<bool> visit;

bool dfs(int cur) {
    visit[cur] = true;

    for (const int& work : graph[cur]) {
        if (!match[work] || (!visit[match[work]] && dfs(match[work]))) {
            match[work] = cur;
            return true;
        }
    }

    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;

    graph.resize(n + 1);
    visit.resize(n + 1);
    match.resize(m + 1, NOT_MATCH);

    for (int i = 1, work_num; i <= n; i++) {
        cin >> work_num;

        for (int j = 1, tmp; j <= work_num; j++) {
            cin >> tmp;
            graph[i].push_back(tmp);
        }
    }

    int match_cnt = 0;
    for (int i = 1; i <= n; i++) {
        fill(visit.begin(), visit.end(), false);
        
        if (dfs(i)) {
            match_cnt++;
        }
    }

    cout << match_cnt;

    return 0;
}