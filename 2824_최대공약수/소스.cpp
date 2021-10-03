#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

typedef long long lli;

constexpr int MAX = 1000000000;

int n, m;
bool over_max = false;
vector<int> prime = { 2 };
unordered_map<int, int> cnt_a, cnt_b;

void init_prime() {
    for (int i = 3; i <= (int)sqrt(MAX); i += 2) {
        bool divided = false;
        for (const int& j : prime) {
            if (i % j == 0) {
                divided = true;
                break;
            }
        }

        if (!divided) {
            prime.push_back(i);
        }
    }
}

void factorization(int n, unordered_map<int, int>& cnt) {
    for (const int& p : prime) {
        if (n % p == 0) {
            cnt.insert(make_pair(p, 0));

            while (n % p == 0) {
                n /= p;
                cnt[p]++;
            }
        }
    }

    if (n > 1) {
        cnt.insert(make_pair(n, 1));
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    init_prime();
    /*
    * ������ ���� ���ؼ� ��� ���μ����ظ� ����,
    * map�� ���μ��� �� ���� ����.
    */
    cin >> n;
    for (int i = 0, tmp; i < n;  i++) {
        cin >> tmp;
        factorization(tmp, cnt_a);
    }
    cin >> m;
    for (int i = 0, tmp; i < m; i++) {
        cin >> tmp;
        factorization(tmp, cnt_b);
    }

    lli res = 1;
    /*
    * �� ������ ��� ������ �ִ� �μ��� �ּڰ���
    * ����� ���ϸ� �� ����� �ִ������̴�.
    */
    for (auto i : cnt_a) {
        int cur = i.first;
        
        if (cnt_b.find(cur) != cnt_b.end()) {
            int power = min(i.second, cnt_b[cur]);

            for (int j = 0; j < power; j++) {
                res *= cur;

                if (res >= MAX) {
                    res %= MAX;
                    over_max = true;
                }
            }
        }
    }

    /*
    * ������� ���߱�
    */
    if (over_max) {
        cout.width(9);
        cout.fill('0');
    }
    cout << res;

    return 0;
}