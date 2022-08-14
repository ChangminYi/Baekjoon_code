#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int NOT_VISIT = -1;

int n, m, cnt;
vector<int> graph[5001], scc_set[5001], scc_head;
int visit_cnt[5001], scc_parent[5001], out_degree[5001];
stack<int> stk;

void clear_var() {
    for(int i = 1; i <= n; i++) {
        graph[i].clear(), scc_set[i].clear();
        visit_cnt[i] = NOT_VISIT, scc_parent[i] = NOT_VISIT, out_degree[i] = 0;
    }
    scc_head.clear();
    while(!stk.empty()) stk.pop();
    cnt = 0;
}

int find_scc(const int cur) {
    int ret = visit_cnt[cur] = ++cnt;
    stk.push(cur);

    for(const int& nxt: graph[cur]) {
        if(visit_cnt[nxt] == NOT_VISIT) ret = min(ret, find_scc(nxt));
        else if(scc_parent[nxt] == NOT_VISIT) ret = min(ret, visit_cnt[nxt]);
    }

    if(ret == visit_cnt[cur]) {
        scc_head.push_back(cur);
        while(true) {
            int tmp = stk.top(); stk.pop();
            scc_parent[tmp] = cur;
            scc_set[cur].push_back(tmp);
            if(tmp == cur) break;
        }
    }
    
    return ret;
}

int main() {
    /**
     * 강한 연결 요소 집합을 찾은 후, 한 집합에서 다른 집합으로
     * 이동할 수 없는 집합, 즉 out_degree가 0인 집합을 모두 찾으면 된다.
     * 만약 다른 집합으로 이동이 가능하다면, 다시 돌아올 수 없는 경우가 생긴다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    while(true) {
        cin >> n;
        if(n == 0) break;
        else cin >> m;

        clear_var();

        for(int v, w; m; m--) {
            cin >> v >> w;
            graph[v].push_back(w);
        }

        for(int i = 1; i <= n; i++) {
            if(visit_cnt[i] == NOT_VISIT) find_scc(i);
        }

        for(int cur = 1; cur <= n; cur++) {
            for(const int& nxt: graph[cur]) {
                if(scc_parent[cur] != scc_parent[nxt]) out_degree[scc_parent[cur]]++;
            }
        }

        vector<int> ans;
        for(const int& head: scc_head) {
            if(out_degree[head] == 0) ans.insert(ans.end(), scc_set[head].begin(), scc_set[head].end());
        }
        sort(ans.begin(), ans.end());

        for(const int& i: ans) {
            cout << i << ' ';
        }
        cout << '\n';
    }

    return 0;
}
