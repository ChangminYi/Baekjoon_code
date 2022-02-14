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
    * x��ǥ�� �ʿ� �����Ƿ� �������� �ʰ� ������.
    * ������ top�� ���� y��ǥ���� �۰ų� ���� ������ pop�ϸ鼭 ���� ����.
    * ���� top�� �ڽŰ� ���� ������ push�Ѵ�. �̸� ���������� �ݺ��Ͽ�
    * �� ���� ������ �ǹ��� �ּ� ���� ����. 0�� �ǹ��� �ƴϹǷ� �����Ѵ�.
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