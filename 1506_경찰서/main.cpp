#include <iostream>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

const int NOT_VISIT = -1;

int n, cnt = 0;
char tmp;
int cost[100], visit_cnt[100];
vector<int> graph[100];
vector<vector<int>> scc_set;
bool finish[100];
stack<int> stk;

int dfs(const int cur) {
    visit_cnt[cur] = ++cnt;
    stk.push(cur);

    int ret = visit_cnt[cur];
    for(const int& nxt: graph[cur]) {
        if(visit_cnt[nxt] == NOT_VISIT) ret = min(ret, dfs(nxt));
        else if(!finish[nxt]) ret = min(ret, visit_cnt[nxt]);
    }

    if(ret == visit_cnt[cur]) {
        vector<int> scc;

        while(true) {
            int val = stk.top(); stk.pop();
            scc.push_back(val);
            finish[val] = true;
            if(cur == val) break;
        }

        scc_set.push_back(scc);
    }

    return ret;
}

int main() {
    /**
     * 간선에 방향이 있고 특정 노드로 갔다가 돌아오는 경로가 있어야 하므로,
     * 그래프에서 강한 연결 요소 집합을 모두 찾으면 된다. 각 집합 내에서 
     * 경찰서를 짓는 비용이 최소인 곳의 비용을 모두 더한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> tmp;
            if(tmp == '1') graph[i].push_back(j);
        }
    }

    fill(visit_cnt, visit_cnt + n, NOT_VISIT);
    for(int i = 0; i < n; i++) {
        if(visit_cnt[i] == NOT_VISIT) dfs(i);
    }

    int ans = 0;
    for(const vector<int>& scc: scc_set) {
        int min_val = cost[scc.front()];
        for(auto i = scc.begin() + 1; i != scc.end(); i++) {
            min_val = min(min_val, cost[*i]);
        }
        ans += min_val;
    }

    cout << ans;

    return 0;
}
