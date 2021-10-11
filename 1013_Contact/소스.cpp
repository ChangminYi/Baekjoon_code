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
        * c++ �⺻ ���̺귯�� regex ����Ͽ�
        * ���Ծ�� ���¿� �´��� Ȯ��
        */
        cout << (regex_match(to_test, re) ? "YES\n" : "NO\n");
    }

    return 0;
}