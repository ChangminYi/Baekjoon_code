#include <iostream>

using namespace std;

int n, cnt;
bool ans_found = false;
int a[500000], b[500000], tmp[500000];

void merge_sort(int lo, int hi) {
    if(lo >= hi) return;
    
    int mid = (lo + hi) / 2;
    merge_sort(lo, mid);
    merge_sort(mid + 1, hi);

    int i = lo, j = mid + 1, idx = lo;
    while(i <= mid && j <= hi) {
        if(a[i] < a[j]) tmp[idx++] = a[i++];
        else tmp[idx++] = a[j++];
    }
    while(i <= mid) tmp[idx++] = a[i++];
    while(j <= hi) tmp[idx++] = a[j++];

    idx = lo;
    while(idx <= hi) {
        if(a[idx] == b[idx]) cnt--;
        a[idx] = tmp[idx], idx++;
        if(a[idx - 1] == b[idx - 1]) cnt++;

        if(!ans_found && cnt == n) ans_found = true;
    }
}

int main() {
    /**
     * 같은 인덱스에서 서로 같은 값을 가지는 원소의 수를 미리 센다.
     * 병합 정렬을 진행하면서, 두 배열이 같아질 수 있는지를 확인한다.
     * 병합을 진행하면서, 병합 전에는 다른 위치였지만 병합 후에 같은 위치가 된
     * 원소들을 추가로 카운트한다. 카운트가 n이 되면 같은 배열이다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    cnt = n;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) {
        cin >> b[i];
        if(a[i] != b[i]) cnt--;
    }

    if(cnt == n)
        cout << 1;
    else {
        merge_sort(0, n - 1);
        cout << (ans_found ? 1 : 0);
    }

    return 0;
}