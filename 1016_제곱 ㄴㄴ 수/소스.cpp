#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

lli lo, hi, res;
vector<bool> divided;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> lo >> hi;
    divided.resize(hi - lo + 1, false);
    res = hi - lo + 1;

    /*
    * sqrt(hi)보다 낮은 모든 제곱수에 대하여 검사
    * 제곱수의 곱 중 lo보다 크거나 같은 최솟값을 구하여
    * 그 범위 안의 값을 모두 걸러냄 (에라토스테네스의 체)
    * 나눠졌다면 카운트 내려준다.
    * 결과는 나뉘지 않은 값들의 수이다.
    */
    for (lli i = 2, base; i * i <= hi; (i == 2 ? i++ : i += 2)) { // 홀수만 보면 계산량 감소
        base = lo / (i * i);
        if (lo % (i * i) > 0) {
            base++;
        }

        while (base * (i * i) <= hi) {
            if (!divided[base * (i * i) - lo]) {
                divided[base * (i * i) - lo] = true;
                res--;
            }
            base++;
        }
    }

    cout << res;
    
    return 0;
}