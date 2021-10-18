#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int n, gcd_val;
vector<int> argi, divisor;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n);
    for (int& i : argi) {
        cin >> i;
    }

    sort(argi.begin(), argi.end());

    /*
    * a = k1 * m + r
    * b = k2 * m + r
    * ...�� ���� ���̱� ������, a-b�� �ϸ� a-b�� �ִ����� m�� ã�� �� �ִ�.
    * �̸� ��� ���� ���ؼ� ����ϰ�, �ִ��������� �ִ������� ���ϸ�
    * �ִ��� m���� ��������. �̸� ���μ������Ͽ� ����ϸ� �ȴ�.
    * ���μ����ص� �ð��� �ɸ��Ƿ�, sqrt(gcd)���� ����Ͽ� ���� �� ���.
    */
    gcd_val = argi[1] - argi[0];
    for (int i = 1; i < n - 1; i++) {
        gcd_val = gcd(gcd_val, argi[i + 1] - argi[i]);
    }

    divisor.push_back(gcd_val);
    for (int i = 2; i * i <= gcd_val; i++) {
        if (gcd_val % i == 0) {
            divisor.push_back(i);

            if (i * i != gcd_val) {
                divisor.push_back(gcd_val / i);
            }
        }
    }

    sort(divisor.begin(), divisor.end());
    for (int& i : divisor) {
        cout << i << ' ';
    }


    return 0;
}