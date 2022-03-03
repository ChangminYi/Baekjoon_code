#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int r, c, lo, hi, mid;
bool flag;
string str[1'000];

bool has_dup(const int base) {
    unordered_set<string> visit;
    for (int i = 0; i < c; i++) {
        string tmp;
        for (int j = base; j < r; j++) {
            tmp += str[j][i];
        }

        if (visit.find(tmp) == visit.end()) visit.insert(tmp);
        else return true;
    }
    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 선형으로 탐색하면 시간초과가 발생한다. 따라서 이분탐색을 진행한다.
    * 문자열을 만들기 시작할 행의 번호로 이분탐색을 진행하고, 그 때 사용하는 mid 값을 저장한다.
    * 만약 마지막 mid 값에서 중복이 있었다면 mid - 1은 중복이 없다. 따라서 답은 mid - 1이 된다.
    * 만약 중복이 없었다면 mid가 정답이 된다. 이 상태를 따로 관리해야 한다.
    */

    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        cin >> str[i];
    }

    lo = 0, hi = r - 1;
    while (lo <= hi) {
        if (flag = has_dup((mid = (lo + hi) / 2))) hi = mid - 1;
        else lo = mid + 1;
    }

    cout << (flag ? mid - 1 : mid);

    return 0;
}