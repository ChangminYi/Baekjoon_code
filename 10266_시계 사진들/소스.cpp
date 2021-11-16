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
    * ȯ�� ���ڿ� Ž��. ã�� ���ڿ��� �� �� �� ���� ���ڿ��� Ž���ϸ� �ȴ�.
    * �ٴ��� ������ Ư�� ������ �ƴϰ�, �ð�� �� ������ �����鼭 ���� ������ ����
    * ���¸��� üũ�ϹǷ�, ������ �����鸸 ǥ�ø� �ϰ� ������ ã���� �ȴ�.
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