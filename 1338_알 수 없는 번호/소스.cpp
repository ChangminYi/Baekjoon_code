#include <iostream>
#include <vector>

using namespace std;

long long l, r, x, y;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 주어지는 수에 범위 제한만이 있기 때문에, 조건에 맞지 않는
    * 입력이 주어지면 일일히 걸러내야 한다. 계산 중에 int를
    * 넘어서는 값이 나오므로 long long을 사용. 값이 1개만 나올 경우
    * 그 답을 출력하고, 아니라면 에러를 출력한다.
    */

    cin >> l >> r >> x >> y;
    if (l > r) swap(l, r);
    if (x < 0) x = -x;

    if (2 * x <= r - l) {
        cout << "Unknwon Number\n";
    }
    else if (y < 0 || y >= x) {
        cout << "Unknwon Number\n";
    }
    else {
        vector<long long> cand;
        long long base;
        if ((l % x + x) % x == y) base = l;
        else if ((l % x + x) % x < y) base = l + y - (l % x + x) % x;
        else base = l + x - (l % x + x) % x - y;

        for (; base <= r; base += x) {
            if ((base % x + x) % x == y) cand.push_back(base);
        }

        if (cand.size() == 1) cout << cand[0] << '\n';
        else cout << "Unknwon Number\n";
    }

    return 0;
}