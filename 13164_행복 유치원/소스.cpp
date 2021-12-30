#include <iostream>
#include <queue>

using namespace std;

int n, k;
priority_queue<int> pq;

int main() {
    long long sum = 0;
    int back_tmp, cur_tmp;
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ������ ������� Ű ���̰� ���� ���� ���� �������� ������,
    * �� ����� �ּҷ� ���� �� �ִ�. ����, �� ���� ���̸� ���
    * ������ �� �����Ͽ� ���� ū �� k-1���� ������ k���� ��������
    * ���� �Ͱ� ����. �� ��, ���� ���̸� ��� ���ϸ� �ȴ�.
    */
    cin >> n >> k;
    cin >> back_tmp;
    for (int i = 1; i < n; i++) {
        cin >> cur_tmp;
        pq.push(cur_tmp - back_tmp);
        back_tmp = cur_tmp;
    }

    for (int i = 0; i < n - 1; i++) {
        if (i >= k - 1) {
            sum += pq.top();
        }
        pq.pop();
    }

    cout << sum;

    return 0;
}