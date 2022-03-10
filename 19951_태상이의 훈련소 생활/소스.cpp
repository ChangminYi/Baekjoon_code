#include <iostream>

using namespace std;

int n, m;
int init_h[100'001], offset[100'001], presum[100'001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * lazy propagation�� ����ϴ� ���׸�Ʈ Ʈ���� ������� �ʾƵ� �ȴ�.
    * ���� ���� �̿��Ͽ� ������ ���ۿ� ��ȭ���� ���ϰ�, ������ �� ���� ��ȣ��
    * ��ȭ���� �ٽ� �� ��, ��ȭ���� �������� ���� ���̿� ���ϸ�
    * ���� ���̸� ���� �� �ִ�.
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