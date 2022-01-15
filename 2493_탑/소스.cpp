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
    * �������� �������� �����ϹǷ�, �������� �������� ���̸� �д´�.
    * ���� ������ top���� ���� ���̰� ���ٸ�, �������� ��� �����ϹǷ�
    * ���ÿ� ���� �ε����� push�Ѵ�. ���� ���̰� ���ٸ�, �� ���� ���̰� ���� ������
    * ������ pop�ϰ�, �ش� �ε������� ���� �ε����� �����Ѵ�. �׸��� ����
    * �ε����� push�Ѵ�. �� ������ �ݺ��ϸ� �ȴ�.
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