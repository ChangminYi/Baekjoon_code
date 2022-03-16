#include <iostream>

using namespace std;

int n;
int arg[1'000'000], buf[1'000'000];

long long merge_sort(const int lo, const int hi) {
    if (lo == hi) return 0;
    else {
        int mid = (lo + hi) / 2;
        long long ret = merge_sort(lo, mid) + merge_sort(mid + 1, hi);

        for (int i = lo, j = mid + 1, idx = lo; idx <= hi; idx++) {
            if (i <= mid && (j > hi || arg[i] < arg[j])) {
                buf[idx] = arg[i++];
            }
            else {
                ret += mid - i + 1;
                buf[idx] = arg[j++];
            }
        }

        for (int i = lo; i <= hi; i++) {
            arg[i] = buf[i];
        }
        return ret;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 큰 것이 작은 것보다 앞에 가 있는 모든 경우를 세야 한다.
    * 병합정렬을 할 때, 두 개의 정렬된 부분 배열에서, 뒷쪽 배열의 값이
    * 앞쪽 배열의 값보다 작다면 이는 순서가 뒤바뀐 것이다. 따라서 이 때
    * 앞쪽 부분 배열에 남은 원소의 수를 계속 더하면 전체 쌍을 구할 수 있다.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
    }

    cout << merge_sort(0, n - 1);

    return 0;
}