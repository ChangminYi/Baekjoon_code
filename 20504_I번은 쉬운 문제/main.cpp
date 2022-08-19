#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

const int NOT_VISIT = -1;

int n, m, t, cnt = 0;
vector<int> graph[200001], scc_head;
int visit_cnt[200001], scc_par[200001];
map<int, bool> in_degree, to_visit;
stack<int> stk;

int find_scc(const int cur) {
    int ret = visit_cnt[cur] = ++cnt;
    stk.push(cur);

    for(const int nxt: graph[cur]) {
        if(visit_cnt[nxt] == NOT_VISIT) ret = min(ret, find_scc(nxt));
        else if(scc_par[nxt] == NOT_VISIT) ret = min(ret, visit_cnt[nxt]);
    }

    if(ret == visit_cnt[cur]) {
        scc_head.push_back(cur);
        while(true) {
            int tmp = stk.top(); stk.pop();
            scc_par[tmp] = cur;
            if(tmp == cur) break;
        }
    }

    return ret;
}

int main() {
    /**
     * 함수가 사이클을 이뤄 호출하는 것을 처리하기 위해 
     * 강한 연결 요소로 묶어준다. 그리고 요소 집합을 위상정렬한 뒤,
     * in_degree가 0인 점을 테스트케이스가 모두 호출하는 지를 판별한다.
     * 모두 호출하면 in_degree가 0인 요소 집합의 수를 출력하고, 아니라면 -1을 출력한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for(int u, v; m--; ) {
        cin >> u >> v;
        graph[u].push_back(v);
    }

    fill(visit_cnt + 1, visit_cnt + n + 1, NOT_VISIT);
    fill(scc_par + 1, scc_par + n + 1, NOT_VISIT);

    for(int i = 1; i <= n; i++) {
        if(visit_cnt[i] == NOT_VISIT) find_scc(i);
    }
    
    for(const int head: scc_head) {
        in_degree.insert(make_pair(head, false));
        to_visit.insert(make_pair(head, true));
    }

    for(int i = 1; i <= n; i++) {
        for(const int j: graph[i]) {
            if(scc_par[i] != scc_par[j]) in_degree[scc_par[j]] = true;
        }
    }

    int zero_head_cnt = 0;
    for(const int head: scc_head) {
        if(in_degree[head] == 0) zero_head_cnt++;
    }

    int enter_cnt = 0;
    cin >> t;
    for(int i, pi; t--; ) {
        cin >> i;
        pi = scc_par[i];
        if(!in_degree[pi] && to_visit[pi]) {
            to_visit[pi] = false;
            enter_cnt++;
        }
    }

    cout << (zero_head_cnt == enter_cnt ? zero_head_cnt : -1);

    return 0;
}
