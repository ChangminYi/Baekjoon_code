#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MIN_LENGTH = 2;
const int MAX_LENGTH = 20;

int n, k;
long long ans;
string tmp;
vector<int> arg[21];

long long get_set(int idx) {
    long long ret = 0, leng;
    int hi = 0;
    for (int i = 0; i < (int)arg[idx].size(); i++) {
        while (hi < (int)arg[idx].size() && arg[idx][hi] - arg[idx][i] <= k) {
            hi++;
        }
        ret += hi - i - 1;
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �̸��� ���̸� �ε����� ���, �� ���̿����� ������� �����Ѵ�.
    * ���� �̸��� ���̸��� ����� ������������ ���ĵ� ���·� �����ȴ�.
    * ���� ���� ����� ���������� ���, ���ذ����� k��ŭ �� ū ������ Ž��.
    * �������� �ϳ��� �������Ѽ� �ݺ��ϰ�, �� ���� ���� ��� ��� ���ϸ� ����.
    */

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        arg[tmp.length()].push_back(i);
    }

    for (int i = MIN_LENGTH; i <= MAX_LENGTH; i++) {
        ans += get_set(i);
    }

    cout << ans;

    return 0;
}