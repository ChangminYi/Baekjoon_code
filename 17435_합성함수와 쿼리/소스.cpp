#include <iostream>
#include <vector>

using namespace std;

const int MAX_ROW = 500001;
const int MAX_COL = 22;

int n, q;
int dp[MAX_ROW][MAX_COL];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    /*
    * 희소배열.
    * 2^i번째 부모를 미리 구한다. 그리고 각 쿼리마다
    * 이 배열의 값을 따라가면 log(n)의 시간복잡도로
    * fn(x)의 값을 찾을 수 있다.
    */
    for (int i = 1; i <= n; i++) {
        cin >> dp[i][0];
    }
    for (int j = 1; j < MAX_COL; j++) {
        for (int i = 1; i <= n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }

    cin >> q;
    /*
    * 부모 구하는 부분.
    * 인자로 들어온 arg1을 비트 단위로 보아서
    * 만약 2^k 꼴이 있으면 그 값만큼 점프
    */
    do {
        int arg1, arg2;
        cin >> arg1 >> arg2;

        for (int i = 0; arg1 > 0; i++, arg1 >>= 1) {
            if (arg1 & 1) {
                arg2 = dp[arg2][i];
            }
        }

        cout << arg2 << '\n';
    } while (--q > 0);

    return 0;
}