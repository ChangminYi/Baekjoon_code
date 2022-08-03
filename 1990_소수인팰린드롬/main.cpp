#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int a, b;
int tmp[11];
vector<int> palin, prime_list;

void dfs(int lo, int hi, int len) {
    if(lo > hi) {
        int val = 0;
        for(int i = 0; i < len; i++) {
            val = (val * 10) + tmp[i];
        }
        palin.push_back(val);
    }
    else {
        for(int i = 0; i <= 9; i++) {
            tmp[lo] = tmp[hi] = i;
            dfs(lo + 1, hi - 1, len);
        }
    }
}

void make_palin() {
    for(int i = 1; i <= 8; i++) {
        for(int j = 1; j <= 9; j++) {
            tmp[0] = tmp[i - 1] = j;
            dfs(1, i - 2, i);
        }
    }
}

bool is_prime(const int val) {
    for(const int& p: prime_list) {
        if(p * p > val) break;
        else if(val % p == 0) return false;
    }
    return true;
}

void init_prime() {
    prime_list.push_back(2);
    for(int i = 3; i * i <= 100000000; i += 2) {
        if(is_prime(i)) prime_list.push_back(i);
    }
}

int main() {
    /**
     * 최대 1억의 범위 안에서 소수를 전부 찾으면 시간이 부족하므로,
     * 팰린드롬인 수를 먼저 모두 생성한 다음 범위 내에서 소수 판정을 한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> a >> b;

    make_palin();
    init_prime();

    for(auto i = lower_bound(palin.begin(), palin.end(), a); i != palin.end() && *i <= b; i++) {
        if(is_prime(*i)) {
            cout << *i << '\n';
        }
    }
    cout << -1;

    return 0;
}
