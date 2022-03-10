#include <iostream>

using namespace std;

int n, m;
int init_h[100'001], offset[100'001], presum[100'001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * lazy propagation을 사용하는 세그먼트 트리를 사용하지 않아도 된다.
    * 누적 합을 이용하여 구간의 시작에 변화량을 더하고, 구간의 끝 다음 번호에
    * 변화량을 다시 뺀 후, 변화량의 누적합을 최초 높이와 더하면
    * 최종 높이를 구할 수 있다.
    */

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> init_h[i];
    }

    for (int lo, hi, val; m; m--) {
        cin >> lo >> hi >> val;
        offset[lo] += val;
        offset[hi + 1] -= val;
    }

    for (int i = 1; i <= n; i++) {
        presum[i] = presum[i - 1] + offset[i];
        cout << init_h[i] + presum[i] << ' ';
    }

    return 0;
}