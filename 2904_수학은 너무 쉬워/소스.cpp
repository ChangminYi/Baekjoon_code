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

    // �Ҽ� ���ϱ�.
    init_prime();
    cin >> n;
    
    /*
    * ������ �Է¿� ���ؼ� ���μ����� ��� ����.
    * ��ü �Ҽ��� ī��Ʈ��, �� ���� ���� ���μ� ���� ����.
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
    * �ִ� ���ڴ� �� �Ҽ��� ���� ��ü ���� ���� ���� �ִ� ��.
    * ������ �Ҽ��� ���ؼ� ��� ����.
    * �ּ� �̵� Ƚ���� ������ ��ŭ �޾ƿ��� Ƚ���� ��.
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