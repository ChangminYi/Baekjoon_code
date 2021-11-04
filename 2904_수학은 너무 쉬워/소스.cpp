#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1000000;

int n;
int prime_cnt[MAX + 1] = { 0 };
vector<int> prime = {2, 3};
vector<vector<int>> matrix;

void init_prime() {
    for (int i = 5; i <= MAX; i += 2) {
        bool divided = false;
        for (auto j = 0; prime[j] * prime[j] <= i; j++) {
            if (i % prime[j] == 0) {
                divided = true;
                break;
            }
        }

        if (!divided) {
            prime.push_back(i);
            prime_cnt[i] = 0;
        }
    }
}

int fast_exp(int base, int exp){
    if (exp == 0) {
        return 1;
    }
    else {
        int res = fast_exp(base, exp / 2);
        res *= res;
        if (exp & 1) {
            res *= base;
        }

        return res;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    // 소수 구하기.
    init_prime();
    cin >> n;
    
    /*
    * 각각의 입력에 대해서 소인수분해 결과 저장.
    * 전체 소수의 카운트와, 각 수에 대한 소인수 따로 저장.
    */
    matrix.resize(n, vector<int>(prime.size(), 0));
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;

        for (int j = 0; i < prime.size() && tmp != 1; j++) {
            while (tmp % prime[j] == 0) {
                tmp /= prime[j];
                prime_cnt[prime[j]]++;
                matrix[i][j]++;
            }
        }
    }

    /*
    * 최대 숫자는 각 소수의 수를 전체 수로 나눈 값이 최대 수.
    * 각각의 소수에 대해서 모두 실행.
    * 최소 이동 횟수는 부족한 만큼 받아오는 횟수의 합.
    */
    int ans = 1, cnt = 0;
    for (int i = 0; i < prime.size(); i++) {
        int cur = prime_cnt[prime[i]] / n;

        for (int j = 0; j < n; j++) {
            if (cur > matrix[j][i]) {
                cnt += cur - matrix[j][i];
            }
        }

        ans *= fast_exp(prime[i], cur);
    }

    cout << ans << ' ' << cnt;

    return 0;
}