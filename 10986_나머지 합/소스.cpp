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
    * 1�� ���Һ��� n�������� ���� ���� sum[n]�̶�� �Ѵ�.
    * j������ i�������� �������� sum[i] - sum[j - 1]�̴�.
    * sum[n] mod m == 0�̰ų� sum[i] mod m == sum[j - 1] mod m �� ���� ����.
    * ���� ���� �Է¹����鼭 ����� ���ϰ�,
    * ���� ���� ����� �� �����Ͽ� �Ŀ� ����� ����.
    */
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        sum += tmp;

        if (sum % m == 0) {
            ans++;
        }
        mod_set[sum % m]++;
    }

    // �����÷ο� ����.
    for (int i = 0; i < m; i++) {
        ans += mod_set[i] * ((lli)mod_set[i] - 1) / 2;
    }

    cout << ans;

    return 0;
}