#include <iostream>
#include <vector>

using namespace std;

int t;
long long a, b, sum;
bool is_prime, not_prime[2'000'001];
vector<long long> prime;

void init_prime() {
    not_prime[0] = not_prime[1] = true;
    for (int i = 4; i <= 2'000'000; i += 2) {
        not_prime[i] = true;
    }
    for (int i = 3; i * i <= 2'000'000; i += 2) {
        if (!not_prime[i]) {
            for (int j = i * i; j <= 2'000'000; j += i) {
                not_prime[j] = true;
            }
        }
    }

    for (int i = 2; i <= 2'000'000; i++) {
        if (!not_prime[i]) {
            prime.push_back(i);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 골드바흐의 추측. 두 수의 합인 4 * 10^12의 제곱근인 2'000'000까지 소수를 모두 구한다.
    * 만약 두 수의 합이 2보다 큰 짝수이면 반드시 그 수는 두 소수의 합으로 나타낼 수 있다.
    * 두 수의 합이 홀수인 경우, 두 수의 합에서 2를 뺀 값이 소수여야 한다.
    */

    init_prime();
    cin >> t;
    do {
        cin >> a >> b;
        sum = a + b;
        if (sum <= 3) cout << "NO\n";
        else if (sum % 2 == 0) cout << "YES\n";
        else {
            sum -= 2;
            is_prime = true;
            for (size_t i = 0; i < prime.size() && prime[i] * prime[i] <= sum; i++) {
                if (sum % prime[i] == 0) {
                    is_prime = false;
                    break;
                }
            }
            cout << (is_prime ? "YES\n" : "NO\n");
        }
    } while (--t);

    return 0;
}