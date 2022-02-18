#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int n;
int arg[1'000], sub[999];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �� ���� ���� ����� �ǵ��� �Է� �迭�� �����Ѵ�.
    * ������ ������ �迭�� ���� ��� ���̰��� �ִ������̴�.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
    }
    sort(arg, arg + n);

    for (int i = 0; i < n - 1; i++) {
        sub[i] = arg[i + 1] - arg[i];
    }

    int ans = sub[0];
    for (int i = 1; i < n - 1; i++) {
        ans = gcd(ans, sub[i]);
    }

    cout << ans;

    return 0;
}