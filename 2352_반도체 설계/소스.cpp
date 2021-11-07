#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> argi, res;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        argi.push_back(tmp);
    }

    /*
    * ���� �� �����ϴ� �κ� ���� ����.
    * ��Ʈ��ŷ�� �ʿ� ������, ������ ũ�⸸ ����ϸ� �ȴ�.
    */
    for (const int& i : argi) {
        if (res.empty() || i > res.back()) {
            res.push_back(i);
        }
        else if (i < res.front()) {
            res[0] = i;
        }
        else {
            *upper_bound(res.begin(), res.end(), i - 1) = i;
        }
    }

    cout << res.size();

    return 0;
}