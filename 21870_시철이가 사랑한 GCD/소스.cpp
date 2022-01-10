#include <iostream>
#include <numeric>
#include <cmath>

using namespace std;

int n;
int arg[200001];

int get_gcd(int lo, int hi) {
    int res = arg[lo];
    for (int i = lo + 1; i <= hi; i++) {
        res = gcd(res, arg[i]);
    }
    return res;
}

long long get_max(int lo, int hi) {
    if (lo == hi) {
        return arg[lo];
    }
    else {
        int mid_lo = (hi - lo + 1) / 2;
        int mid_hi = (int)(((double)hi - lo + 1) / 2 + 0.5);
        long long res1 = get_max(lo, hi - mid_hi) + get_gcd(hi - mid_hi + 1, hi);
        long long res2 = get_max(lo + mid_lo, hi) + get_gcd(lo, lo + mid_lo - 1);
        return max(res1, res2);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 분할 정복을 통해 최댓값을 계산하면 된다. 다만, 부분 배열의 범위를
    * 계산할 때 조건을 잘 구현해야 한다.
    */
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arg[i];
    }

    cout << get_max(1, n);

    return 0;
}