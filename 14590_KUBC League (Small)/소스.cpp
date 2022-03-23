#include <iostream>
#include <vector>

using namespace std;

const int NOT_VISIT = -1;
const int CONNECTED = 1;

int n, all_visit;
vector<int> adj[20];
int dp[20][1 << 20];

int get_max_dist(const int cur, const int visit_bit) {
    int& ret = dp[cur][visit_bit];
    if (ret == NOT_VISIT) {
        ret = 0;
        for (const int nxt: adj[cur]) {
            if((visit_bit & (1 << nxt)) == 0) {
                ret = max(ret, get_max_dist(nxt, visit_bit | (1 << nxt)) + 1);
            }
        }
    }

    return ret;
}

void track_dp(const int cur, const int visit_bit) {
    for (const int nxt: adj[cur]) {
        if ((visit_bit & (1 << nxt)) == 0 && dp[cur][visit_bit] == dp[nxt][visit_bit | (1 << nxt)] + 1) {
            cout << nxt + 1 << ' ';
            track_dp(nxt, visit_bit | (1 << nxt));
            break;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���ǿ� ��ȸ ������ ����. �ٸ�, ������ ũ��Ӹ� �ƴ϶� ���� ��ü��
    * ����ؾ� �ϱ� ������, dp �迭�� ���� �����ϴ� ����� ����
    * dp �迭�� �ٽ� �����Ͽ� ������ ����Ѵ�.
    */

    cin >> n;
    all_visit = (1 << n) - 1;
    for (int i = 0, tmp; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            if (tmp == CONNECTED) adj[i].push_back(j);
        }
        fill(dp[i], dp[i] + (1 << n), NOT_VISIT);
    }

    cout << get_max_dist(0, 1 << 0) + 1 << "\n1 ";
    track_dp(0, 1 << 0);

    return 0;
}