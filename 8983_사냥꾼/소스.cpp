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
    * 사대를 정렬하여, 각각의 동물에 대해서 사대를 탐색하도록 함
    */
    place.resize(m);
    for (int &i : place) {
        cin >> i;
    }
    sort(place.begin(), place.end());

    /*
    * 이분탐색을 실행. 끝까지 탐색하지는 않음.
    * 거리 식인 |x - a| + b <= L를 풀면, a + b - L <= x <= a - b + L가 된다.
    * 따라서 최솟값을 이분탐색하여, 중간 값이 범위 내에 들게 된다면
    * 동물을 사냥할 수 있으므로, 카운트해준다.
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