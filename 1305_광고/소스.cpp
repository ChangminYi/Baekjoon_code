#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
string str;
vector<int> pi;

void init_pi() {
    for (int i = 1, j = 0; i < n; i++) {
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

    cin >> n;
    cin >> str;
    pi.resize(n, 0);

    /*
    * kmp �˰��� ����. ���� ª�� ���̸� ���ؾ� �ϹǷ�,
    * ���ڿ����� ���� �� ���λ�/���̻��� ���̸� ��ü ���̿��� ���� �� ���� ����.
    * ���� �� ���λ�/���̻��� ���̴� pi[n-1]�� ��.
    */
    init_pi();

    cout << n - pi[n - 1];

    return 0;
}