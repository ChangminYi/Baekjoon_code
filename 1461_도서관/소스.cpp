#include <iostream>
#include <queue>

using namespace std;

int n, m;
priority_queue<int> positive, negative;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ��� �κа� ���� �κ��� ������ ����.
    * m���� ����� ��, ���� �ָ� �ִ� å�� �Ÿ��� �̵��ؾ� �� �Ÿ�.
    * �� �Ÿ��� ��� ���ϰ�, 2��� �ø��� �պ� �̵��Ÿ��� �ȴ�.
    * 0���� ���� �ʿ䰡 �����Ƿ�, ���� �� �Ÿ� �� ���� ����� �Ѵ�.
    */
    cin >> n >> m;
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        tmp > 0 ? positive.push(tmp) : negative.push(-tmp);
    }

    int sum = 0, max_dist = 0;
    while (!positive.empty()) {
        for (int i = 0; i < m && !positive.empty(); i++, positive.pop()) {
            if (i == 0) {
                sum += positive.top();
                max_dist = max(max_dist, positive.top());
            }
        }
    }
    while (!negative.empty()) {
        for (int i = 0; i < m && !negative.empty(); i++, negative.pop()) {
            if (i == 0) {
                sum += negative.top();
                max_dist = max(max_dist, negative.top());
            }
        }
    }

    cout << 2 * sum - max_dist;

    return 0;
}