#include <iostream>
#include <stack>

using namespace std;

int g;
stack<int> stk;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> g;

    /*
    * a^2 - b^2 = g, (a + b)(a - b) = g (a > b)
    * a - b�� i�� �����Ͽ� a + b�� ���ϰ�,
    * �̸� ���Ͽ� a�� ���Ѵ�.
    * ��, a > b�̹Ƿ� i * i < g (���� ���� ���� ����)
    */
    for (int i = 1; i * i < g; i++) {
        if (g % i == 0) {
            int plus = g / i, minus = i;
            int a = (plus + minus) / 2;
            int b = plus - a;

            if ((a + b) * (a - b) == g) {
                stk.push(a);
            }
        }
    }

    if (stk.empty()) {
        cout << -1;
    }
    else {
        for (; !stk.empty(); stk.pop()) {
            cout << stk.top() << '\n';
        }
    }

    return 0;
}