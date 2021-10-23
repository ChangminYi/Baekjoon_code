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
    * 짝수는 모두 2에서 걸러지니, 다음부터는 홀수만 체크
    * 만약 i가 소수라면, i의 제곱수부터는 아직 체크가 안 된 수들 존재.
    * i보다 작은 수들이 공약수로 있는 경우는 이미 걸러졌기 때문.
    * 가장 작은 공약수를 저장하여 다음으로 봐야 할 노드 계산 가능.
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
* 큐에 순서대로 출력할 순서 저장.
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