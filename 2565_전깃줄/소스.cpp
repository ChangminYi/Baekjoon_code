#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
pint arg[100];
vector<int> dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� �� �����ϴ� �κм��� ����. �ٸ�, ������ ������� ������ �����Ƿ�,
    * ���� ������ ���� ������ �� �� �޾� ���� �������� ����. �� �� ������ ��������
    * ���� �� �����ϴ� �κм����� ���̸� ���ϰ�, ������ ������ ���� ����.
    */
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].first >> arg[i].second;
    }

    sort(arg, arg + n);

    for (int i = 0; i < n; i++) {
        if (dp.empty() || dp.back() < arg[i].second) {
            dp.push_back(arg[i].second);
        }
        else {
            auto lb = lower_bound(dp.begin(), dp.end(), arg[i].second);
            *lb = arg[i].second;
        }
    }

    cout << n - dp.size();

    return 0;
}