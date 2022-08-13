#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int NOT_VISIT = -1;

int t, n, m, cnt;
vector<int> graph[100001], scc_head;
int visit_cnt[100001], parent[100001], in_degree[100001];
stack<int> stk;

int find_scc(const int cur) {
    int ret = visit_cnt[cur] = ++cnt;
    stk.push(cur);

    for(const int& nxt: graph[cur]) {
        if(visit_cnt[nxt] == NOT_VISIT) ret = min(ret, find_scc(nxt));
        else if(parent[nxt] == NOT_VISIT) ret = min(ret, visit_cnt[nxt]);
    }

    if(ret == visit_cnt[cur]) {
        scc_head.push_back(cur);

        while(true) {
            int tmp = stk.top(); stk.pop();
            parent[tmp] = cur;
            if(tmp == cur) break;
        }
    }

    return ret;
}

void clear_var() {
    for(int i = 1; i <= n; i++) {
        graph[i].clear(), visit_cnt[i] = NOT_VISIT;
        parent[i] = NOT_VISIT, in_degree[i] = 0;
    }
    while(!stk.empty()) stk.pop();
    scc_head.clear();
    cnt = 0;
}

int main() {
    /**
     * 강한 연결 요소의 집합 간의 연결을 봐야 한다. 집합 간 연결에서,
     * 집합으로 들어오는 간선이 없다면 그 집합 중 하나의 노드를
     * 넘어뜨려야 한다. 따라서 in_degree가 0인 집합의 수가 정답이다.
     * 그리고 최소한 1개의 도미노는 직접 밀어야 한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    do {
        cin >> n >> m;

        clear_var();

        for(int u, v; m; m--) {
            cin >> u >> v;
            graph[u].push_back(v);
        }

        for(int i = 1; i <= n; i++) {
            if(visit_cnt[i] == NOT_VISIT) find_scc(i);
        }

        for(int i = 1; i <= n; i++) {
            for(const int& adj: graph[i]) {
                if(parent[i] != parent[adj]) in_degree[parent[adj]]++;
            }
        }

        int ans = 0;
        for(const int& head: scc_head) {
            if(in_degree[head] == 0) ans++;
        }

        cout << max(ans, 1) << '\n';
    } while(--t);

    return 0;
}
