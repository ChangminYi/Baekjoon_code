#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int arg[200];
vector<int> dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� �� �����ϴ� �κм��� ����. ������� �� �ִ� ��ȣ�� ���� �ִ� ��ȣ�� �̾��,
    * �ٸ� ���а� �����ϴ� ������ ���� �Űܾ� �ϴ� ������ ���� ����. ���� ��ü �ο�����
    * ���� �� �����ϴ� �κм����� ���̸� �� ���� ����.
    */
    cin >> n;
    for (int i = 0; i < n;  i++) {
        cin >> arg[i];
    }

    for (int i = 0; i < n; i++) {
        if (dp.empty() || dp.back() < arg[i]) {
            dp.push_back(arg[i]);
        }
        else {
            auto lb = lower_bound(dp.begin(), dp.end(), arg[i]);
            *lb = arg[i];
        }
    }

    cout << n - dp.size();

    return 0;
}