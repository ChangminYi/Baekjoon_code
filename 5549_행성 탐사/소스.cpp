#include <iostream>

using namespace std;

int n, m, k;
char tmp;
int cnt_j[1'001][1'001], cnt_o[1'001][1'001], cnt_i[1'001][1'001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * (1, 1)에서부터 (i, j)로 직사각형을 그렸을 때, 그 안에 있는 지역의 수를 저장한다.
    * 들어오는 쿼리의 범위에 맞춰 구역을 나눠서 계산하면 된다.
    */

    cin >> m >> n >> k;
    for (int i = 1; i <= m; i++) {
        for (int j = 1, row_j = 0, row_o = 0, row_i = 0; j <= n; j++) {
            cin >> tmp;
            if (tmp == 'J') row_j++;
            else if (tmp == 'O') row_o++;
            else row_i++;
            cnt_j[i][j] = cnt_j[i - 1][j] + row_j;
            cnt_o[i][j] = cnt_o[i - 1][j] + row_o;
            cnt_i[i][j] = cnt_i[i - 1][j] + row_i;
        }
    }

    for (int lo_r, lo_c, hi_r, hi_c, ans_j, ans_o, ans_i; k; k--) {
        cin >> lo_r >> lo_c >> hi_r >> hi_c;
        ans_j = cnt_j[hi_r][hi_c] - cnt_j[hi_r][lo_c - 1] - cnt_j[lo_r - 1][hi_c] + cnt_j[lo_r - 1][lo_c - 1];
        ans_o = cnt_o[hi_r][hi_c] - cnt_o[hi_r][lo_c - 1] - cnt_o[lo_r - 1][hi_c] + cnt_o[lo_r - 1][lo_c - 1];
        ans_i = cnt_i[hi_r][hi_c] - cnt_i[hi_r][lo_c - 1] - cnt_i[lo_r - 1][hi_c] + cnt_i[lo_r - 1][lo_c - 1];
        cout << ans_j << ' ' << ans_o << ' ' << ans_i << '\n';
    }

    return 0;
}