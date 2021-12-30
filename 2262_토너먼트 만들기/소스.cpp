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
    * �ݵ�� ���ڰ� ���� ����� �¸��ϰ� �ǹǷ�, ���ڰ� ���� �����
    * ���� �ö󰡰� �Ǹ� ������ Ŀ����. ����, ���� ū ���� ���� ���ָ鼭
    * ������ ���ϸ� �ȴ�.
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