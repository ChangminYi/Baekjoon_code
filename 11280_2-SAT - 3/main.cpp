#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int NOT_VISIT = -1;

int n, m, cnt;
int scc[20001], visit_cnt[20001];
bool finish[20001];
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
        else if(!finish[nxt]) ret = min(ret, visit_cnt[nxt]);
    }

    if(ret == visit_cnt[cur]) {
        while(true) {
            int tmp = stk.top(); stk.pop();
            finish[tmp] = true;
            scc[tmp] = cur;
            if(tmp == cur) break;
        }
    }

    return ret;
}

int main() {
    /**
     * (x1 v x2)가 참이 되려면, ~x1 -> x2 혹은 ~x2 -> x1이어야 한다.
     * 그리고 모든 or 절이 참이 되어야 2-CNF 식이 참이 된다.
     * 이를 그래프로 표현하고, 강한 연결 요소 집합를 구한다.
     * 만약 x와 ~x가 같은 집합에 있으면 그 식은 반드시 거짓이다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);    
    
    cin >> n >> m;
    // t: 1 ~ n, f: n+1 ~ 2n
    for(int a, b; m--; ) {
        cin >> a >> b;
        if(a < 0) a = n - a;
        if(b < 0) b = n - b;

        graph[get_opp(a)].push_back(b);
        graph[get_opp(b)].push_back(a);
    }

    fill(visit_cnt + 1, visit_cnt + 2 * n + 1, NOT_VISIT);
    for(int i = 1; i <= 2 * n; i++)
        if(visit_cnt[i] == NOT_VISIT) find_scc(i);

    int ans = 1;
    for(int i = 1; i <= n && ans == 1; i++) {
        if(scc[i] == scc[get_opp(i)])
            ans = 0;
    }

    cout << ans;

    return 0;
}