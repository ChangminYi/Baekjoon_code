#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
vector<pint> arg;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> arg[i].first;
        arg[i].second = i;
    }

    sort(arg.begin(), arg.end());

    /*
    * ���� ��Ʈ�� �� �� ������ ���� �ִ� �� ĭ �������� ���Ƿ�,
    * �����ϱ� ���� ������ ���� �ε��� ���̸� ���� �ȴ�.
    */
    int max_dist = 0;
    for (int i = 0; i < n; i++) {
        max_dist = max(max_dist, arg[i].second - i);
    }

    cout << max_dist + 1;

    return 0;
}