#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX = 101;
const char WILDCARD = '*';
const int NOT_VISIT = -1;
const int REJECT = 0;
const int ACCEPT = 1;

int testcase;
string patt, sear;
vector<vector<int>> dp(MAX, vector<int>(MAX));

int match_str(int p_idx, int s_idx) {
    int& result = dp[p_idx][s_idx];

    if (result != NOT_VISIT) {
        return result;  //�̹� �˻縦 �� �κ��� �ٷ� �� ��ȯ
    }
    else {
        // ���ϰ� �׽�Ʈ�� Ư�� ���ڰ� ���� ���
        if (p_idx < patt.length() && s_idx < sear.length() && patt[p_idx] == sear[s_idx]) {
            return result = match_str(p_idx + 1, s_idx + 1);
        }

        // ���ϰ� �׽�Ʈ�� ������ �� ���
        if (p_idx == patt.length() && s_idx == sear.length()) {
            return result = ACCEPT;
        }

        // ���Ͽ� ���ϵ�ī�尡 ���� ���
        if (patt[p_idx] == WILDCARD) {
            // ���ϵ�ī�� ���� ���ڰ� ��ġ�� ��� (���ϵ�ī���� ���� = 0)
            if (match_str(p_idx + 1, s_idx)) {
                return result = ACCEPT;
            }
            // ���ϵ�ī���� ���̰� 1 �̻��� ���
            else if (s_idx < sear.length() && match_str(p_idx, s_idx + 1)) {
                return result = ACCEPT;
            }
        }

        return result = REJECT;
    }
}



int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    (cin >> patt >> testcase).ignore();

    do {
        cin >> sear;
        for (vector<int>& row : dp) {
            fill(row.begin(), row.end(), NOT_VISIT);
        }

        if (match_str(0, 0) == ACCEPT) {
            cout << sear << '\n';
        }
    } while (--testcase > 0);

    return 0;
}