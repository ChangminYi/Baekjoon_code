#include <iostream>
#include <vector>
#include <string>

using namespace std;

string str;
vector<int> pi;

void init_pi() {
    pi = vector<int>(str.length(), 0);

    for (int i = 1, j = 0; i < str.length(); i++) {
        while (j > 0 && str[i] != str[j]) {
            j = pi[j - 1];
        }

        if (str[i] == str[j]) {
            pi[i] = ++j;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * kmp �˰����� failure function�� Ȱ��.
    * pi.back()�� ���ڿ��� ���� �� ���λ�/���̻��� ����.
    * ���ڿ��� ���̰� �ִ� ���λ��� ���̷� �������� �� ���� ����,
    * �ƴ϶�� 1�� ����.
    */
    while (cin >> str) {
        if (str == ".") {
            break;
        }
        else {
            init_pi();

            if (pi.back() == 0 || pi.back() % (str.length() - pi.back()) != 0) {
                cout << 1 << '\n';
            }
            else {
                cout << str.length() / (str.length() - pi.back()) << '\n';
            }
        }
    }

    return 0;
}