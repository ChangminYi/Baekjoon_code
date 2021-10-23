#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

const int MAX = 5000000;

int n, k;
int min_prime[MAX + 1];
queue<int> to_print;

void init() {
    iota(min_prime, min_prime + MAX + 1, 0);

    /*
    * ¦���� ��� 2���� �ɷ�����, �������ʹ� Ȧ���� üũ
    * ���� i�� �Ҽ����, i�� ���������ʹ� ���� üũ�� �� �� ���� ����.
    * i���� ���� ������ ������� �ִ� ���� �̹� �ɷ����� ����.
    * ���� ���� ������� �����Ͽ� �������� ���� �� ��� ��� ����.
    */
    for (int i = 2; i * i <= MAX; i == 2 ? i++ : i += 2) {
        if (min_prime[i] == i) {
            for (int j = i * i; j <= MAX; j += i) {
                if (min_prime[j] == j) {
                    min_prime[j] = i;
                }
            }
        }
    }
}

/*
* ť�� ������� ����� ���� ����.
*/
void get_primes(int n) {
    if (n > 1) {
        to_print.push(min_prime[n]);
        get_primes(n / min_prime[n]);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    init();

    cin >> n;
    do {
        cin >> k;

        get_primes(k);
        while (!to_print.empty()) {
            cout << to_print.front();
            to_print.pop();

            cout << (to_print.empty() ? '\n' : ' ');
        }
    } while (--n > 0);

    return 0;
}