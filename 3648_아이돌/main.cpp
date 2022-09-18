#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

const int NOT_VISIT = -1;

int n, m, cnt, scc_num;
int scc[2001], visit_cnt[2001];
vector<int> graph[2001];
stack<int> stk;
string tmp;

int not_x(const int x) {
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

void init_var() {
    fill(scc + 1, scc + 2 * n + 1, NOT_VISIT);
    fill(visit_cnt, visit_cnt + 2 * n + 1, NOT_VISIT);
    for(int i = 1; i <= 2 * n; i++) graph[i].clear();
    cnt = 0, scc_num = 0;
}

int main() {
    /**
     * 2-SAT 문제에서, x1이 true인지를 판단해야 한다.
     * 테스트케이스의 수가 정해지지 않았으므로, getline을 사용하여
     * 입력 버퍼가 끝날 때까지 입력을 받는다. 그 후, SCC를 사용하여
     * 2-SAT의 해를 구하고, 조건에 맞게 결과를 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);    
    
    while(getline(cin, tmp)) {
        for(int i = 0; i < tmp.length(); i++) {
            if(tmp[i] == ' ') {
                n = stoi(tmp.substr(0, i));
                m = stoi(tmp.substr(i + 1));
                break;
            }
        }
        init_var();

        for(int a, b; m--; ) {
            cin >> a >> b;
            if(a < 0) a = n - a;
            if(b < 0) b = n - b;

            graph[not_x(a)].push_back(b);
            graph[not_x(b)].push_back(a);
        }

        fill(visit_cnt + 1, visit_cnt + 2 * n + 1, NOT_VISIT);
        fill(scc + 1, scc + 2 * n + 1, NOT_VISIT);
        for(int i = 1; i <= 2 * n; i++)
            if(visit_cnt[i] == NOT_VISIT) find_scc(i);

        int flag = true;
        for(int i = 1; i <= n && flag; i++)
            if(scc[i] == scc[not_x(i)]) flag = false;

        if(flag && scc[1] < scc[not_x(1)]) cout << "yes\n";
        else cout << "no\n";

        cin.ignore();
    }

    return 0;
}