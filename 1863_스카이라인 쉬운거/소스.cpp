#include <iostream>
#include <stack>

using namespace std;

int n, ans;
int arg[50'000];
stack<int> stk;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * x좌표는 필요 없으므로 저장하지 않고 버린다.
    * 스택의 top이 현재 y좌표보다 작거나 같을 때까지 pop하면서 수를 센다.
    * 만약 top이 자신과 같지 않으면 push한다. 이를 마지막까지 반복하여
    * 센 수의 총합이 건물의 최소 수와 같다. 0은 건물이 아니므로 제외한다.
    */

    cin >> n;
    for (int i = 0, dummy; i < n; i++) {
        cin >> dummy >> arg[i];
    }

    for (int i = 0; i < n; i++) {
        while (!stk.empty() && arg[i] < stk.top()) {
            if (stk.top() > 0) ans++;
            stk.pop();
        }
        if (stk.empty() || stk.top() != arg[i]) {
            stk.push(arg[i]);
        }
    }
    while (!stk.empty()) {
        if (stk.top() > 0) ans++;
        stk.pop();
    }

    cout << ans;

    return 0;
}