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
    * kmp 알고리즘 응용. 가장 짧은 길이를 구해야 하므로,
    * 문자열에서 가장 긴 접두사/접미사의 길이를 전체 길이에서 빼면 그 값이 정답.
    * 가장 긴 접두사/접미사의 길이는 pi[n-1]의 값.
    */
    init_pi();

    cout << n - pi[n - 1];

    return 0;
}