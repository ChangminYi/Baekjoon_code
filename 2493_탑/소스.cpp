#include <iostream>
#include <stack>

using namespace std;

int n;
int arg[500001], rec_idx[500001];
stack<int> stk;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 레이저가 좌측으로 진행하므로, 우측에서 좌측으로 높이를 읽는다.
    * 만약 스택의 top보다 현재 높이가 낮다면, 레이저는 계속 진행하므로
    * 스택에 현재 인덱스를 push한다. 현재 높이가 높다면, 더 높은 높이가 나올 때까지
    * 스택을 pop하고, 해당 인덱스에는 현재 인덱스를 저장한다. 그리고 현재
    * 인덱스를 push한다. 이 과정을 반복하면 된다.
    */
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arg[i];
    }

    for (int i = n; i > 0; i--) {
        if (!stk.empty() && arg[i] > arg[stk.top()]) {
            for (; !stk.empty() && arg[i] > arg[stk.top()]; stk.pop()) {
                rec_idx[stk.top()] = i;
            }
        }
        stk.push(i);
    }
    for (; !stk.empty(); stk.pop()) {
        rec_idx[stk.top()] = 0;
    }

    for (int i = 1; i <= n; i++) {
        cout << rec_idx[i] << ' ';
    }

    return 0;
}