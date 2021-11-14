#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

string str;

int get_max_len(const string& s) {
    int ret = 0;
    vector<int> pi(s.length(), 0);

    for (int i = 1, j = 0; i < s.length(); i++) {
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }

        if (s[i] == s[j]) {
            pi[i] = ++j;
        }

        ret = max(ret, pi[i]);
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> str;

    /*
    * kmp �˰����� failure function�� Ȱ��.
    * pi ���� ���� Ŭ ��, �� ���� 2�� �̻� ������ ���� �κ� ���ڿ��� ����.
    * �ٸ�, �κ� ���ڿ��� �������� ������� �𸣹Ƿ�, ���ڿ��� ���� �� ���ڸ�
    * �ϳ��ϳ� ���ְ��鼭 ��� ��츦 ���캻��.
    */
    int res = 0;
    for (int i = 0; i < str.length(); i++) {
        string tmp = str.substr(i);
        res = max(res, get_max_len(tmp));
    }

    cout << res;

    return 0;
}