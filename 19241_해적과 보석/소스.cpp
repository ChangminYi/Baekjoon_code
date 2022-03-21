#include <iostream>
#include <algorithm>

using namespace std;

struct dat {
    int value_a, value_b, total_val;
    bool operator<(const dat& other) const { return total_val > other.total_val; }
};

int testcase, n;
dat arg[100'000];
int sum[2];

int get_ans() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].value_a >> arg[i].value_b;
        arg[i].total_val = arg[i].value_a + arg[i].value_b;
    }
    fill(sum, sum + 2, 0);

    sort(arg, arg + n);

    for (int i = 0, cur; i < n; i++) {
        cur = (i & 1 ? 1 : 0);
        sum[cur] += (cur == 0 ? arg[i].value_a : arg[i].value_b);
    }

    return sum[0] - sum[1];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ������ �ִ��� ���� ��������, �� ��������� ��ġ�� ���̰� ���� ū ����
    * ���� �Ѵ�. ����, �� ����� ��ġ�� ���� �������� �������� �����Ͽ�
    * ������� ���� �� ���� ���� ���ϸ� �ȴ�.
    */

    cin >> testcase;
    do {
        cout << get_ans() << '\n';
    } while (--testcase);

    return 0;
}