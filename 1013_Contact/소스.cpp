#include <iostream>
#include <string>
#include <regex>

using namespace std;

int t;
regex re("((100+1+|01)+)");
string to_test;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> to_test;
        /*
        * c++ 기본 라이브러리 regex 사용하여
        * 정규언어 형태에 맞는지 확인
        */
        cout << (regex_match(to_test, re) ? "YES\n" : "NO\n");
    }

    return 0;
}