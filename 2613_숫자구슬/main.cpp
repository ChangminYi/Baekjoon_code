#include <iostream>
#include <cmath>

using namespace std;

int n, m, lo = 0, hi = 0;
int arg[300];

bool is_divisible(const int val) {
    int cnt = 1;
    
    for(int i = 0, sum = 0; i < n; i++) {
        sum += arg[i];
        if(sum > val) 
            sum = arg[i], cnt++;
    }

    return cnt <= m;
}

int main() {
    /**
     * 이분 탐색을 통해 그룹의 합의 최댓값의 최솟값을 찾는다.
     * 이분 탐색의 lo와 hi의 초기값은 각각 원소의 최댓값과 원소의 총합이다.
     * 마지막 이분 탐색이 끝난 뒤의 lo 값이 합의 최댓값의 최솟값이다.
     * 최솟값을 기준으로 앞에서부터 그룹을 끊어내며 m 값을 줄인다.
     * 남아 있는 원소의 수가 남아 있는 집합의 수와 같아지면 한 개씩 그룹짓는다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> arg[i];
        lo = max(lo, arg[i]), hi += arg[i];
    }

    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        is_divisible(mid) ? hi = mid - 1 : lo = mid + 1;
    }

    cout << lo << '\n';
    for(int i = 0, sum = 0, cnt = 0; i < n; i++) {
        sum += arg[i];
        if(sum > lo) {
            cout << cnt << ' ';
            cnt = 0, sum = arg[i], m--;
        }
        cnt++;

        if(n - i == m) {
            while(m--) {
                cout << cnt << ' ';
                cnt = 1;
            }
            break;
        }
    }

    return 0;
}