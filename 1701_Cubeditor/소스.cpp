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
    * kmp 알고리즘의 failure function을 활용.
    * pi 값이 가장 클 때, 그 값이 2번 이상 나오는 최장 부분 문자열의 길이.
    * 다만, 부분 문자열의 시작점이 어디인지 모르므로, 문자열의 가장 앞 글자를
    * 하나하나 없애가면서 모든 경우를 살펴본다.
    */
    int res = 0;
    for (int i = 0; i < str.length(); i++) {
        string tmp = str.substr(i);
        res = max(res, get_max_len(tmp));
    }

    cout << res;

    return 0;
}