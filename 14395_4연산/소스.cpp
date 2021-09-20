#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

typedef long long lli;

constexpr char LAST = '.';

lli s, t;
unordered_map<lli, lli> trace;
unordered_map<lli, char> sym;
queue<lli> que;

void print_trace(lli cur) {
    if (cur == s) {
        return;
    }
    else {
        print_trace(trace[cur]);
        cout << sym[cur];
    }
}

bool in_range(const lli n) {
    return 1 <= n && n <= 1000000000;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> s >> t;
    
    if (s == t) {
        cout << 0;
    }
    else {
        trace.insert(make_pair(s, LAST));
        que.push(s);

        /*
        * s = s - s 연산은 0을 만드는데, 0에 들어가면 범위 안의
        * 어떤 수도 만들 수 없으므로 구현에서 제외한다.
        * 오버플로우를 막기 위해서 long long을 사용했고,
        * 정답 출력은 t부터 s까지 거슬러 올라가면서 재귀적으로 하였다.
        */
        bool ans_found = false;
        while (!que.empty()) {
            lli cur = que.front();
            que.pop();

            if (cur == t) {
                ans_found = true;
                break;
            }
            else {
                lli tmp = cur * cur;
                if (in_range(tmp) && trace.find(tmp) == trace.end()) {
                    trace.insert(make_pair(tmp, cur));
                    sym.insert(make_pair(tmp, '*'));
                    que.push(tmp);
                }
                tmp = cur + cur;
                if (in_range(tmp) && trace.find(tmp) == trace.end()) {
                    trace.insert(make_pair(tmp, cur));
                    sym.insert(make_pair(tmp, '+'));
                    que.push(tmp);
                }
                tmp = cur / cur;
                if (in_range(tmp) && trace.find(tmp) == trace.end()) {
                    trace.insert(make_pair(tmp, cur));
                    sym.insert(make_pair(tmp, '/'));
                    que.push(tmp);
                }
            }
        }

        if (ans_found) {
            print_trace(t);
        }
        else {
            cout << -1;
        }
    }

    return 0;
}