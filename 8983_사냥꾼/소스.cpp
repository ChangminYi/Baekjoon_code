#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, L, cnt = 0;
vector<int> place;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> m >> n >> L;

    /*
    * ��븦 �����Ͽ�, ������ ������ ���ؼ� ��븦 Ž���ϵ��� ��
    */
    place.resize(m);
    for (int &i : place) {
        cin >> i;
    }
    sort(place.begin(), place.end());

    /*
    * �̺�Ž���� ����. ������ Ž�������� ����.
    * �Ÿ� ���� |x - a| + b <= L�� Ǯ��, a + b - L <= x <= a - b + L�� �ȴ�.
    * ���� �ּڰ��� �̺�Ž���Ͽ�, �߰� ���� ���� ���� ��� �ȴٸ�
    * ������ ����� �� �����Ƿ�, ī��Ʈ���ش�.
    */
    for (int i = 0, a, b; i < n; i++) {
        cin >> a >> b;

        if (b <= L) {
            int lb = a + b - L, ub = a - b + L;

            int left = 0, right = m - 1;
            while (left <= right) {
                int mid = (left + right) / 2;

                if (lb <= place[mid] && place[mid] <= ub) {
                    cnt++;
                    break;
                }
                else {
                    if (place[mid] < lb) {
                        left = mid + 1;
                    }
                    else {
                        right = mid - 1;
                    }
                }
            }
        }
    }

    cout << cnt;
    
    return 0;
}