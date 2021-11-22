#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n, m, t;
vector<pint> arg, dp;

bool cmp(const pint& lhs, const pint& rhs) {
    return (lhs.first <= rhs.first && lhs.second <= rhs.second);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> t;
    
    for (int i = 0, r, c; i < t; i++) {
        cin >> r >> c;

        if (r <= n && c <= m) {
            arg.push_back(pint(r, c));
        }
    }

    /*
    * O(nlogn)�� ���� �� �����ϴ� �κм��� ����.
    * ���� ���� ��θ��� ����ؾ� �ϹǷ�, ���� ��ġ���� ���� ��ġ��
    * ���� ��ǥ�� ���� ��ǥ���� r, c���� ��� ũ�ų� ���� ��,
    * �� cmp �Լ��� true�� �����̴�. �׸���, �̵���δ� ������
    * ������ �ƴϸ� �Ʒ� �����̹Ƿ�, pair�� ���� ����� �̿��Ͽ�
    * ���� �� ������ ���� �� �ֵ��� ������� ��ǥ���� �������ش�.
    * �� �Ŀ� ���� �� �����ϴ� �κм��� ���̸� ���ϸ� �ȴ�.
    */
    sort(arg.begin(), arg.end());

    dp.push_back(arg[0]);
    for (size_t i = 1; i < arg.size(); i++) {
        if (cmp(dp.back(), arg[i])) {
            dp.push_back(arg[i]);
        }
        else {
            auto lb = lower_bound(dp.begin(), dp.end(), arg[i], cmp);
            *lb = arg[i];
        }
    }

    cout << dp.size();
    
    return 0;
}