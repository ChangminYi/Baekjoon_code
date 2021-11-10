#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, m, weight;
vector<int> pend;
bool dp[31][15001] = { false };

void init_dp(int idx, int cur_weight) {
    if (!dp[idx][cur_weight]) {
        dp[idx][cur_weight] = true;

        if (idx < n) {
            /*
            * 일반적인 배낭 문제에서 경우가 하나 추가된다.
            * 추를 반대편에 놓을 경우, 측정하는 무게가 줄어든 것으로 봐야 한다.
            * 따라서, 추를 놓지 않기/놓기/반대편에 놓기 세 가지를 계산.
            */
            init_dp(idx + 1, cur_weight);
            init_dp(idx + 1, cur_weight + pend[idx]);
            init_dp(idx + 1, abs(cur_weight - pend[idx]));
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    pend.resize(n);
    for (int& i : pend) {
        cin >> i;
    }
    
    /*
    * 배낭 문제. n개의 추를 사용하여 만들 수 있는 모든 무게를 먼저 계산한다.
    * 그 후, 입력받은 무게를 만들 수 있는지 판정하면 된다.
    */
    init_dp(0, 0);

    cin >> m;
    do {
        cin >> weight;

        if (weight > 15000) {
            cout << 'N' << ' ';
        }
        else {
            cout << (dp[n][weight] ? 'Y' : 'N') << ' ';
        }
    } while (--m);

    return 0;
}