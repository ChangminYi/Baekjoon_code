#include <iostream>
#include <stack>

using namespace std;

int n;
long long ans;
int arg[80'000];
stack<int> stk;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 자신보다 작은 빌딩은 자신을 볼 수 없으므로 pop.
    * 이 때 스택의 크기를 정답에 더해주고, 자신의 높이를 push.
    * 이를 반복하면 모든 건물에 대해서 보이는 건물의 총합을
    * 구할 수 있다.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
    }

    for (int i = 0; i < n; i++) {
        while (!stk.empty() && stk.top() <= arg[i]) {
            stk.pop();
        }
        ans += stk.size();
        stk.push(arg[i]);
    }

    cout << ans;

    return 0;
}