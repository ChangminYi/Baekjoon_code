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
    * �ڽź��� ���� ������ �ڽ��� �� �� �����Ƿ� pop.
    * �� �� ������ ũ�⸦ ���信 �����ְ�, �ڽ��� ���̸� push.
    * �̸� �ݺ��ϸ� ��� �ǹ��� ���ؼ� ���̴� �ǹ��� ������
    * ���� �� �ִ�.
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