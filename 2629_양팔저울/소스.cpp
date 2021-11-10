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
            * �Ϲ����� �賶 �������� ��찡 �ϳ� �߰��ȴ�.
            * �߸� �ݴ��� ���� ���, �����ϴ� ���԰� �پ�� ������ ���� �Ѵ�.
            * ����, �߸� ���� �ʱ�/����/�ݴ��� ���� �� ������ ���.
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
    * �賶 ����. n���� �߸� ����Ͽ� ���� �� �ִ� ��� ���Ը� ���� ����Ѵ�.
    * �� ��, �Է¹��� ���Ը� ���� �� �ִ��� �����ϸ� �ȴ�.
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