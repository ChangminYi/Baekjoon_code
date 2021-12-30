#include <iostream>
#include <deque>
#include <cmath>

using namespace std;

int n;
deque<int> deq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    deq.resize(n);
    for (int& i : deq) {
        cin >> i;
    }

    /*
    * 반드시 숫자가 낮은 사람이 승리하게 되므로, 숫자가 높은 사람이
    * 위로 올라가게 되면 총합이 커진다. 따라서, 가장 큰 값을 먼저 없애면서
    * 총합을 구하면 된다.
    */
    int sum = 0;
    for (; n > 1; n--) {
        for (int i = 0; i < n; i++) {
            if (deq[i] == n) {
                if (i == 0) {
                    sum += deq[i] - deq[i + 1];
                }
                else if (i == n - 1) {
                    sum += deq[i] - deq[i - 1];
                }
                else {
                    sum += deq[i] - max(deq[i + 1], deq[i - 1]);
                }

                deq.erase(deq.begin() + i);
                break;
            }
        }
    }

    cout << sum;

    return 0;
}