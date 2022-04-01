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
    * 1�� ���ϰų� 2�� ���ϴ� �������� �����ϸ� �����ϴ�.
    * ����, �Է� �迭�� 1�� ���ų� 2�� ������ �������� ����.
    * ���� ��� �迭�� ���Ұ� ¦�����, 2�� ������ ���� �̵��̴�.
    * ���� 2�� ������ ���� �켱���� �Ͽ� ��� ���Ҹ� 0���� ����� �ȴ�.
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