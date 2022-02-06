#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
pint arg[1000'000];

bool comp(const pint& lhs, const pint& rhs) {
    return lhs.second < rhs.second;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� �������� �������� �����Ѵ�. ���� ������ �����Ϻ��� �����Ͽ�,
    * ������ �ҿ� �ð��� ��ġ�� ���, �� ���� �����ؾ� �ϹǷ� ���� �Ͽ���
    * �ҿ� �ϼ��� ���ش�. �ƴ϶��, �� ������ ����� �����Ƿ�
    * �� ���� �����ϴ� ������ �ֽ�ȭ���ش�.
    */
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].first >> arg[i].second;
    }

    sort(arg, arg + n, comp);

    int ans = arg[n - 1].second - arg[n - 1].first;
    for (int i = n - 2; i >= 0; i--) {
        if (ans >= arg[i].second) ans = arg[i].second - arg[i].first;
        else ans -= arg[i].first;
    }

    cout << ans;

    return 0;
}