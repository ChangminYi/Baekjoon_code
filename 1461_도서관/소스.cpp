#include <iostream>
#include <queue>

using namespace std;

int n, m;
priority_queue<int> positive, negative;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 양수 부분과 음수 부분을 나눠서 생각.
    * m개를 골랐을 때, 가장 멀리 있는 책의 거리가 이동해야 할 거리.
    * 그 거리를 계속 더하고, 2배로 늘리면 왕복 이동거리가 된다.
    * 0에서 끝날 필요가 없으므로, 가장 긴 거리 한 번은 빼줘야 한다.
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