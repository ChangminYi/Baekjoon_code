#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
vector<pint> arg;

bool cmp(const pint& lhs, const pint& rhs){
    return (lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second < rhs.second);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n);
    for (pint& p : arg) {
        cin >> p.first >> p.second;
    }

    /*
    * �׸����ϰ� ����. ������ �ð��� �������� ����.
    * ó������ Ž���Ͽ� ���� ȸ�Ǹ� �� �� ���������� ������Ʈ.
    */
    sort(arg.begin(), arg.end(), cmp);

    int ans = 0, last_fin = 0;
    for (const pint& p : arg) {
        if (last_fin <= p.first) {
            last_fin = p.second;
            ans++;
        }
    }

    cout << ans;

    return 0;
}