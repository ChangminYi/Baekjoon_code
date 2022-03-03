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
    * �������� Ž���ϸ� �ð��ʰ��� �߻��Ѵ�. ���� �̺�Ž���� �����Ѵ�.
    * ���ڿ��� ����� ������ ���� ��ȣ�� �̺�Ž���� �����ϰ�, �� �� ����ϴ� mid ���� �����Ѵ�.
    * ���� ������ mid ������ �ߺ��� �־��ٸ� mid - 1�� �ߺ��� ����. ���� ���� mid - 1�� �ȴ�.
    * ���� �ߺ��� �����ٸ� mid�� ������ �ȴ�. �� ���¸� ���� �����ؾ� �Ѵ�.
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