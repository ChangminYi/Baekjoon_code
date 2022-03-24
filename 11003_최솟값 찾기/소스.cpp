#include <iostream>
#include <queue>
#include <cmath>
#include <functional>

using namespace std;

struct dat {
    int val, idx;
    dat(int _v = 0, int _i = 0) : val(_v), idx(_i) {}
    bool operator>(const dat& other) const { return val > other.val; }
};

int n, l, base;
priority_queue<dat, vector<dat>, greater<>> pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �켱���� ť�� ������������ �����Ѵ�. ���� �ε����� ���� �����Ͽ�
    * ������ ���� �ʴ� �ּڰ��� top�̶�� pop�Ѵ�. �׸��� ���� �ε�����
    * ���� ������ ����, top�� ���� ����ϸ� �ȴ�.
    */

    cin >> n >> l;
    for (int i = 1, val; i <= n; i++) {
        cin >> val;
        
        base = max(1, i - l + 1);
        while (!pq.empty() && pq.top().idx < base) {
            pq.pop();
        }
        pq.push(dat(val, i));

        cout << pq.top().val << ' ';
    }

    return 0;
}