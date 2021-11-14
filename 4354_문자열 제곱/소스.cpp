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
    * kmp 알고리즘의 failure function을 활용.
    * pi.back()은 문자열의 가장 긴 접두사/접미사의 길이.
    * 문자열의 길이가 최대 접두사의 길이로 나눠지면 그 값이 정답,
    * 아니라면 1이 정답.
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