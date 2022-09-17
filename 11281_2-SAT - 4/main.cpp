#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int NOT_VISIT = -1;

int n, m, cnt, scc_num;
int scc[20001], visit_cnt[20001];
vector<int> graph[20001];
stack<int> stk;

int get_opp(const int x) {
    if(x > n) return x - n;
    else return x + n;
}

int find_scc(const int cur) {
    stk.push(cur);
    int ret = visit_cnt[cur] = ++cnt;

    for(const int& nxt: graph[cur]) {
        if(visit_cnt[nxt] == NOT_VISIT) ret = min(ret, find_scc(nxt));
        else if(scc[nxt] == NOT_VISIT) ret = min(ret, visit_cnt[nxt]);
    }

    if(ret == visit_cnt[cur]) {
        scc_num++;
        while(true) {
            int tmp = stk.top(); stk.pop();
            scc[tmp] = scc_num;
            if(tmp == cur) break;
        }
    }

    return ret;
}

int main() {
    /**
     * SCC를 통해 입력으로 주어진 2-SAT 식의 해가 있는지를 먼저 판별한다.
     * 만약 있는 경우, 같은 컴포넌트 안의 모든 변수는 같은 해를 가진다.
     * 변수 x가 ~x보다 빠른 SCC 순서를 가지면 x는 true이고, 아니면 false.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);    
    
    cin >> n >> m;
    for(int a, b; m--; ) {
        cin >> a >> b;
        if(a < 0) a = n - a;
        if(b < 0) b = n - b;

        graph[get_opp(a)].push_back(b);
        graph[get_opp(b)].push_back(a);
    }

    fill(visit_cnt + 1, visit_cnt + 2 * n + 1, NOT_VISIT);
    fill(scc + 1, scc + 2 * n + 1, NOT_VISIT);
    for(int i = 1; i <= 2 * n; i++)
        if(visit_cnt[i] == NOT_VISIT) find_scc(i);

    int ans = 1;
    for(int i = 1; i <= n && ans == 1; i++) {
        if(scc[i] == scc[get_opp(i)])
            ans = 0;
    }

    cout << ans;
    if(ans == 1) {
        cout << '\n';
        for(int i = 1; i <= n; i++)
            cout << (scc[i] < scc[get_opp(i)] ? 1 : 0) << ' ';
    }

    return 0;
}