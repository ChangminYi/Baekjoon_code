#include <iostream>
#include <string>
#include <numeric>

using namespace std;

int n, k;
string arg[15];
int num[15], len[15], d_mod[51];
long long dp[1 << 15][101];

int main() {
    /**
     * 비트마스킹을 통해 사용한 숫자를 저장한다.
     * 현재 값에 다음 숫자를 이어붙여 dp 테이블의 값을 채운다.
     * 50자리 숫자는 저장이 불가능하므로, 모두 k로 나눠 관리한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arg[i];
        len[i] = arg[i].length();
    }
    cin >> k;
    for(int i = 0; i < n; i++) {
        for(const char& c: arg[i])
            num[i] = (10 * num[i] + (c - '0')) % k;
    }
    d_mod[0] = 1;
    for(int i = 1; i <= 50; i++)
        d_mod[i] = (d_mod[i - 1] * 10) % k;

    dp[0][0] = 1;
    for(int visit_bit = 0; visit_bit < (1 << n); visit_bit++) {
        for(int cur_val = 0; cur_val < k; cur_val++) {
            for(int nxt_idx = 0; nxt_idx < n; nxt_idx++) {
                if(visit_bit & (1 << nxt_idx)) continue;
                int nxt_val = (cur_val * d_mod[len[nxt_idx]] + num[nxt_idx]) % k;
                dp[visit_bit | (1 << nxt_idx)][nxt_val] += dp[visit_bit][cur_val];
            }
        }
    }

    long long res = dp[(1 << n) - 1][0], t_cnt = 1;
    for(int i = 2; i <= n; i++)
        t_cnt *= i;
    long long g = gcd(t_cnt, res);
    cout << res / g << '/' << t_cnt / g;

    return 0;
}