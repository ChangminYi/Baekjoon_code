#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lli;

int n;
vector<int> argi;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n);
    for (int& i : argi) {
        cin >> i;
    }
    sort(argi.begin(), argi.end());

    /*
    * i�� j�� �����ϸ�, -(argi[i] + argi[j])��
    * (j+1, n]�� �������� ã���� �ȴ�.
    * ������ �� ���� ���� ���� ���� �� �����Ƿ�,
    * upper_bound�� lower_bound�� ����Ͽ� �ߺ� ������ ã��
    * ��ü ī��Ʈ�� �����ش�.
    */
    lli cnt = 0;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            int tmp_sum = argi[i] + argi[j];

            auto lb = lower_bound(argi.begin() + j + 1, argi.end(), -tmp_sum);
            auto ub = upper_bound(argi.begin() + j + 1, argi.end(), -tmp_sum);

            cnt += distance(lb, ub);
        }
    }

    cout << cnt;

    return 0;
}