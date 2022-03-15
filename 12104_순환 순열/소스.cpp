#include <iostream>
#include <string>

using namespace std;

string a, b;
int pi[100'000];

void init_pi() {
    for (int i = 1, j = 0; i < (int)a.length(); i++) {
        while (j > 0 && a[i] != a[j]) j = pi[j - 1];
        if (a[i] == a[j]) pi[i] = ++j;
    }
}

int kmp() {
    int ret = 0;

    init_pi();
    for (int i = 0, j = 0; i < (int)b.length(); i++) {
        while (j > 0 && b[i] != a[j]) j = pi[j - 1];
        if (b[i] == a[j]) {
            if (j == a.length() - 1) {
                ret++;
                j = pi[j];
            }
            else j++;
        }
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * XOR하여 0이 나오려면, a와 b 문자열이 모두 일치해야 한다.
    * 문자열이 순환하기 때문에, 원본 문자열의 길이 - 1만큼의 부분 문자열을
    * 원본 문자열에 이어붙여서 원형으로 탐색하듯이 만들어준다. 문자열 탐색은
    * kmp 알고리즘을 사용한다.
    */

    cin >> a >> b;
    b += b.substr(0, b.length() - 1);

    cout << kmp();

    return 0;
}