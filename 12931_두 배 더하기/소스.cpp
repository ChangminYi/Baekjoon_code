#include <iostream>

using namespace std;

int n, cnt = 0;
int arg[50];

bool is_all_zero() {
    for (int i = 0; i < n; i++) if (arg[i]) return false;
    return true;
}

bool can_divide_by_two() {
    for (int i = 0; i < n; i++) if (arg[i] & 1) return false;
    return true;
}

void do_divide() {
    for (int i = 0; i < n; i++) {
        arg[i] >>= 1;
    }
}

void do_minus() {
    for (int i = 0; i < n; i++) {
        if (arg[i] & 1) {
            arg[i]--;
            break;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 1을 더하거나 2를 곱하는 방향으로 접근하면 복잡하다.
    * 따라서, 입력 배열을 1을 빼거나 2로 나누는 방향으로 접근.
    * 만약 모든 배열의 원소가 짝수라면, 2로 나누는 것이 이득이다.
    * 따라서 2로 나누는 것을 우선으로 하여 모든 원소를 0으로 만들면 된다.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
    }

    for (; !is_all_zero(); cnt++) {
        if (can_divide_by_two()) do_divide();
        else do_minus();
    }

    cout << cnt;

    return 0;
}