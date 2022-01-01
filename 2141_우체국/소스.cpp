#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;

int n;
lli right_sum = 0, left_sum = 0;
pint arg[100000];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n;i++) {
        cin >> arg[i].first >> arg[i].second;
        right_sum += arg[i].second;
    }

    /*
    * ���� ��ȣ�� ���ĵ��� �ʾ��� ���� �����Ƿ�, ���� ������� �����Ѵ�.
    * �� ��, ������ ���� �����հ� ���� �������� ���� ���Ͽ�, ���̰� ����
    * ���� ���� ��ü���� ���� �� ���̴�.
    */
    sort(arg, arg + n);

    lli diff = INT64_MAX;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        left_sum += arg[i].second;
        lli tmp_diff = abs(right_sum - left_sum);
        right_sum -= arg[i].second;
        
        if (tmp_diff < diff) {
            idx = i;
            diff = tmp_diff;
        }
    }

    cout << arg[idx].first;

    return 0;
}