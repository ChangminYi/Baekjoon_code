#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int NOT_VISIT = -1;

int t, n, m, cnt = 0;
vector<int> graph[100000], scc_set[100000], scc_head;
int visit_cnt[100000], in_degree[100000], scc_par[100000];
stack<int> stk;

void clear_var() {
    for(int i = 0; i < n; i++) {
        graph[i].clear(), scc_set[i].clear();
    }
    scc_head.clear();
    fill(visit_cnt, visit_cnt + n, NOT_VISIT);
    fill(in_degree, in_degree + n, 0);
    fill(scc_par, scc_par + n, NOT_VISIT);
    while(!stk.empty()) stk.pop();
    cnt = 0;
}

int find_scc(const int cur) {
    int ret = visit_cnt[cur] = ++cnt;
    stk.push(cur);

    for(const int& nxt: graph[cur]) {
        if(visit_cnt[nxt] == NOT_VISIT) ret = min(ret, find_scc(nxt));
        else if(scc_par[nxt] == NOT_VISIT) ret = min(ret, visit_cnt[nxt]);
    }

    if(ret == visit_cnt[cur]) {
        scc_head.push_back(cur);
        while(true) {
            int tmp = stk.top(); stk.pop();
            scc_set[cur].push_back(tmp);
            scc_par[tmp] = cur;
            if(tmp == cur) break;
        }
    }

    return ret;
}

int main() {
    /**
     * 강한 연결 요소 집합의 진입 차수를 따져야 한다.
     * 만약 집합 중 진입 차수가 0인 집합이 단 1개 있다면, 다른 모든 노드에 접근 가능.
     * 2개 이상이라면 진입 차수가 0인 다른 집합에는 도달할 수 없음.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    do {
        cin >> n >> m;
        clear_var();
        for(int a, b; m; m--) {
            cin >> a >> b;
            graph[a].push_back(b);
        }

        for(int i = 0; i < n; i++) {
            if(visit_cnt[i] == NOT_VISIT) find_scc(i);
        }

        for(int cur = 0; cur < n; cur++) {
            for(const int& nxt: graph[cur]) {
                if(scc_par[cur] != scc_par[nxt]) in_degree[scc_par[nxt]]++;
            }
        }

        int set_cnt = 0, idx = 0;
        for(const int& head: scc_head) {
            if(in_degree[head] == 0) set_cnt++, idx = head;
        }

        if(set_cnt == 1) {
            sort(scc_set[idx].begin(), scc_set[idx].end());
            for(const int& node: scc_set[idx]) {
                cout << node << '\n';
            }
            cout << '\n';
        }
        else cout << "Confused\n\n";
    } while(--t);

    return 0;
}
