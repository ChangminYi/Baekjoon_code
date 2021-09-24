#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

constexpr int ALPHA_SIZE = 26;

int n;
vector<string> args;
vector<int> alpha(ALPHA_SIZE);

int main() {
    cin.tie(nullptr);

    cin >> n;
    args.resize(n);
    for (string& s : args) {
        cin >> s;
    }

    /*
    * 알파벳 별로 자릿수의 합을 모두 구하고,
    * 그 합이 가장 큰 알파벳부터 9, 8, ...을 할당
    * 모두 더하면 최댓값
    */
    for (const string& s : args) {
        for (auto i = s.rbegin(); i != s.rend(); i++) {
            alpha[*i - 'A'] += (int)pow(10, distance(s.rbegin(), i));
        }
    }

    sort(alpha.rbegin(), alpha.rend());
    int res = 0;
    for (int i = 0, base = 9; i < ALPHA_SIZE && alpha[i] > 0; i++) {
        res += alpha[i] * base--;
    }

    cout << res;

    return 0;
}