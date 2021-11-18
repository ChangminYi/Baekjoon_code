#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

int n;
vector<int> arg, merge_arg;

lli merge_sort(int lo, int hi) {
    if (lo == hi) {
        return 0;
    }
    else {
        int mid = (lo + hi) / 2;
        lli res = merge_sort(lo, mid) + merge_sort(mid + 1, hi);

        // 부분 배열 정렬. 교차점의 수도 같이 더한다.
        for (int i = lo, j = mid + 1, idx = 0; i <= mid || j <= hi; ) {
            if (i <= mid && (j > hi || arg[i] <= arg[j])) {
                merge_arg[idx++] = arg[i++];
            }
            else {
                res += (1LL + mid) - i;
                merge_arg[idx++] = arg[j++];
            }
        }

        // 정렬된 부분 배열 원래 배열에 덮어쓰기
        for (int i = lo; i <= hi; i++) {
            arg[i] = merge_arg[i - lo];
        }

        return res;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n), merge_arg.resize(n);
    for (int& i : arg) {
        cin >> i;
    }

    /*
    * 병합 정렬을 활용하여 교차점 세기. 일종의 세그먼트 트리와 비슷한 형태.
    * 정렬된 상태의 전체 배열과, 그 배열을 반으로 나눈 두 배열이 있다고 하면,
    * 같은 원소를 이을 때의 교차점의 수는 버블 정렬에서의 스왑 횟수와 같다.
    * 재귀적으로 정렬을 수행하며 그때마다 횟수 계산.
    */
    cout << merge_sort(0, n - 1);

    return 0;
}