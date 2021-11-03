#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

int n, m;
lli sum = 0, ans = 0;
vector<int> mod_set;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> m;
    mod_set.resize(m, 0);

    /*
    * 1번 원소부터 n번까지의 누적 합을 sum[n]이라고 한다.
    * j번부터 i번까지의 누적합은 sum[i] - sum[j - 1]이다.
    * sum[n] mod m == 0이거나 sum[i] mod m == sum[j - 1] mod m 두 가지 존재.
    * 앞의 경우는 입력받으면서 결과에 더하고,
    * 뒤의 경우는 경우의 수 저장하여 후에 결과에 더함.
    */
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        sum += tmp;

        if (sum % m == 0) {
            ans++;
        }
        mod_set[sum % m]++;
    }

    // 오버플로우 조심.
    for (int i = 0; i < m; i++) {
        ans += mod_set[i] * ((lli)mod_set[i] - 1) / 2;
    }

    cout << ans;

    return 0;
}