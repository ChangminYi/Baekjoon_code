#include <iostream>

using namespace std;

int n;
int arg[200000], tmp[200000];
long long cnt = 0;

void merge_sort(int lo, int hi) {
    int mid = (lo + hi) / 2;
    if(lo < mid) merge_sort(lo, mid);
    if(mid + 1 < hi) merge_sort(mid + 1, hi);

    int left = lo, right = mid + 1, idx = lo;
    for(; left <= mid && right <= hi; ) {
        if(arg[left] < arg[right]) tmp[idx++] = arg[left++];
        else cnt += (mid - left + 1), tmp[idx++] = arg[right++];
    }

    while(left <= mid) tmp[idx++] = arg[left++];
    while(right <= hi) tmp[idx++] = arg[right++];
    for(idx = lo; idx <= hi; idx++) arg[idx] = tmp[idx];
}

int main() {
    /**
     * 인버전 카운팅. 두 수의 스왑에 제약사항이 걸려 있지만,
     * n개의 수가 1부터 n으로 이뤄져 있으므로 정렬이 가능하다.
     * 따라서, 머지 소트를 사용하여 인버전의 수를 세면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arg[i];

    merge_sort(0, n - 1);

    cout << cnt;

    return 0;
}