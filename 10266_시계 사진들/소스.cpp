#include <iostream>

using namespace std;

const int MAX = 360000;

int n;
bool arg_a[2 * MAX + 1] = { false };
bool arg_b[MAX + 1] = { false };
int pi[MAX + 1] = { 0 };

void init_pi() {
    for (int i = 1, j = 0; i < MAX; i++) {
        while (j > 0 && arg_b[i] != arg_b[j]) {
            j = pi[j - 1];
        }

        if (arg_b[i] == arg_b[j]) {
            pi[i] = ++j;
        }
    }
}

bool kmp() {
    for (int i = 0, j = 0; i < 2 * MAX; i++) {
        while (j > 0 && arg_a[i] != arg_b[j]) {
            j = pi[j - 1];
        }

        if (arg_a[i] == arg_b[j]) {
            if (j == MAX - 1) {
                return true;
            }
            else {
                j++;
            }
        }
    }

    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    /*
    * 환형 문자열 탐색. 찾는 문자열을 한 번 더 이은 문자열을 탐색하면 된다.
    * 바늘의 각도가 특정 순서가 아니고, 시계는 한 바퀴를 돌리면서 같은 각도를 가진
    * 형태만을 체크하므로, 등장한 각도들만 표시를 하고 패턴을 찾으면 된다.
    */
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        arg_a[tmp] = arg_a[tmp + MAX] = true;
    }
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        arg_b[tmp] = true;
    }

    init_pi();
    
    cout << (kmp() ? "possible" : "impossible");

    return 0;
}