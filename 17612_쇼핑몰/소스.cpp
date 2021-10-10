#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
struct comp {
    bool operator()(pint& lhs, pint& rhs) {
        return (lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first > rhs.first);
    }
};

int n, k, cus_id, item_n, line_id, wait_t;
lli res;
bool all_lined = false;
vector<queue<pint>> lines;
priority_queue<pint, vector<pint>, greater<pint>> min_pq;
priority_queue<pint, vector<pint>, comp> out_pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    lines.resize(k);

    /*
    * �ϴ� ���� ��ȣ�� ������� �� �� �ִ´�.
    * n���� �� �־����� break�Ѵ�.
    * �׸��� ���������� ������ pq�� �ִ´�.
    */
    for (int i = 0; i < k; i++) {
        if (i >= n) {
            all_lined = true;
            break;
        }
        else {
            cin >> cus_id >> item_n;
            lines[i].push(pint(item_n, cus_id));
            min_pq.push(pint(item_n, i));
        }
    }

    /*
    * ���� ���뿡 ���� ���� ����� �����ִ� ���.
    * ���� ����� ���������� ���뿡 ���� ����� �ִ´�.
    */
    if (!all_lined) {
        for (int i = k; i < n; i++) {
            cin >> cus_id >> item_n;

            line_id = min_pq.top().second;
            wait_t = min_pq.top().first + item_n;
            min_pq.pop();

            lines[line_id].push(pint(wait_t, cus_id));
            min_pq.push(pint(wait_t, line_id));
        }
    }

    /*
    * ������ ������ ���Ѵ�.
    * �� ���뿡�� ù ��°�� ����� ��ġ�� ������� ����.
    * ���� �ִ� �ο� �Ѿ�� ������.
    */
    for (int i = 0; i < k; i++) {
        if (i >= n) {
            break;
        }
        else {
            out_pq.push(pint(lines[i].front().first, i));
        }
    }

    /*
    * ��� �� ��� �� ���� ��� �ٽ� pq�� �ֱ�
    * ������� ���� ����� �� ��ȣ�� ���� ����� ����������
    * �� ����� pq�� �־ ���� ������ ����Ѵ�.
    * �����÷ο� ����
    */
    for (lli i = 1; i <= (lli)n; i++) {
        line_id = out_pq.top().second;
        out_pq.pop();
        cus_id = lines[line_id].front().second;
        lines[line_id].pop();

        res += i * cus_id;
        if (!lines[line_id].empty()) {
            out_pq.push(pint(lines[line_id].front().first, line_id));
        }
    }

    cout << res;

    return 0;
}