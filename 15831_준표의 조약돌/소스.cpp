#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int n, b, w, ans;
string str;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 최대 길이가 30만이므로, dp로는 시간을 맞출 수 없다.
    * 문자열의 첫 번째부터 훑으면서, 조건을 만족하는 가장 긴 구간을 찾아
    * 길이를 구하고, 그 길이의 최댓값을 출력하면 된다.
    */

    cin >> n >> b >> w;
    cin >> str;
    
    for (int lo = 0, hi = 0, w_cnt = 0, b_cnt = 0; hi < n; hi++) {
        if (str[hi] == 'W') w_cnt++;
        else b_cnt++;

        if (w_cnt >= w && b_cnt <= b) {
            ans = max(ans, hi - lo + 1);
        }
        else if (b_cnt > b) {
            while (lo <= hi && b_cnt > b) {
                if (str[lo] == 'W') w_cnt--;
                else b_cnt--;
                lo++;
            }
        }
        else continue;
    }

    cout << ans;

    return 0;
}