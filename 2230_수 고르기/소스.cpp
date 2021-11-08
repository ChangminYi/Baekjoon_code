#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

int n, m;
int diff = INT32_MAX;
vector<int> argi;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        argi.push_back(tmp);
    }
    sort(argi.begin(), argi.end());

    /*
    * ���� ��, ���̰� m-1�� �ʰ��ϴ� ���� ã��.
    * ������ �� �̻� Ž���� �ʿ䰡 �����Ƿ� ������ Ż���ϰ�,
    * �ִٸ� �� �� ���̸� ������Ʈ.
    */
    for (int i = 0; i < n; i++) {
        auto ub = upper_bound(argi.begin() + i, argi.end(), argi[i] + m - 1);
        
        if (ub == argi.end()) {
            break;
        }
        else {
            diff = min(diff, *ub - argi[i]);
        }
    }

    cout << diff;

    return 0;
}