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
    * �ִ� ���̰� 30���̹Ƿ�, dp�δ� �ð��� ���� �� ����.
    * ���ڿ��� ù ��°���� �����鼭, ������ �����ϴ� ���� �� ������ ã��
    * ���̸� ���ϰ�, �� ������ �ִ��� ����ϸ� �ȴ�.
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