#include <iostream>
#include <queue>
#include <functional>

using namespace std;

typedef long long lli;

const lli MOD = 1000000007;

int testcase, n;
lli tmp, res;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    do {
        priority_queue<lli, vector<lli>, greater<lli>> pq;
        
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> tmp;
            pq.push(tmp);
        }

        res = 1;
        while (pq.size() > 1) {
            tmp = pq.top();
            pq.pop();
            tmp *= pq.top();
            pq.pop();
            
            res = tmp % MOD * res % MOD;
            pq.push(tmp);
        }

        cout << res << '\n';
    } while (--testcase > 0);

    return 0;
}