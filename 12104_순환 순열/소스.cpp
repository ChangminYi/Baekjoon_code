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
    * XOR�Ͽ� 0�� ��������, a�� b ���ڿ��� ��� ��ġ�ؾ� �Ѵ�.
    * ���ڿ��� ��ȯ�ϱ� ������, ���� ���ڿ��� ���� - 1��ŭ�� �κ� ���ڿ���
    * ���� ���ڿ��� �̾�ٿ��� �������� Ž���ϵ��� ������ش�. ���ڿ� Ž����
    * kmp �˰����� ����Ѵ�.
    */

    cin >> a >> b;
    b += b.substr(0, b.length() - 1);

    cout << kmp();

    return 0;
}