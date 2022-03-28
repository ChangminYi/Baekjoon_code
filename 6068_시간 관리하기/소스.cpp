#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct node {
    int len, bound;
    bool operator<(const node& other) const { return bound < other.bound; }
};

int n, ans = INT32_MAX;
node arg[1'000];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� ������ ���� �������� ����.
    * �׸��� �������� ���� �����ؾ� �ϴ� �ð��� ���� ������ �ð� ��
    * ���� ������ ���� ���� �ɸ��� �ð��� ���� ���� ���� �����ؾ�
    * �ϴ� �ð��� ��������.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].len >> arg[i].bound;
    }

    sort(arg, arg + n);

    for (int i = n - 1; i >= 0; i--) {
        ans = min(ans, arg[i].bound);
        ans -= arg[i].len;
    }

    cout << (ans >= 0 ? ans : -1);

    return 0;
}