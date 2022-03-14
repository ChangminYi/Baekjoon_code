#include <iostream>
#include <numeric>

using namespace std;

int n, ans;
int pi[1'000'000];
char rullet[2'000'000], to_find[1'000'000];

void init_pi() {
    for (int i = 1, j = 0; i < n; i++) {
        while (j > 0 && to_find[i] != to_find[j]) j = pi[j - 1];
        if (to_find[i] == to_find[j]) pi[i] = ++j;
    }
}

void kmp() {
    init_pi();

    for (int i = 0, j = 0; i < 2 * n - 1; i++) {
        while (j > 0 && rullet[i] != to_find[j]) j = pi[j - 1];
        if (rullet[i] == to_find[j]) {
            if (j == n - 1) {
                ans++;
                j = pi[j];
            }
            else j++;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���ڿ��� ȯ������ �����ǹǷ�, ������ ���ڸ� ������ ���ڿ��� ���� ���ڿ���
    * �̾�ٿ� Ž���Ѵ�. ���� ���ڿ� Ž���� ���ؼ� kmp �˰��� ���.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> rullet[i];
        rullet[i + n] = rullet[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> to_find[i];
    }

    kmp();

    int res_gcd = gcd(ans, n);
    cout << ans / res_gcd << '/' << n / res_gcd;

    return 0;
}