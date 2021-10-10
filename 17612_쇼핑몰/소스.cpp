#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
struct pq_n {
    int line_n = 0, out_time = 0, cus_id = 0;
    pq_n(int line, int time, int id) : line_n(line), out_time(time), cus_id(id) {}
    bool operator>(const pq_n& rhs) const {
        if (this->out_time == rhs.out_time) {
            return this->line_n < rhs.line_n;
        }
        return this->out_time > rhs.out_time;
    }
};

lli n, k, res;
vector<queue<pint>> line;
priority_queue<pint, vector<pint>, greater<pint>> line_out_pq;
priority_queue<pq_n, vector<pq_n>, greater<pq_n>> total_out_pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;

    /*
    * ��� ������ ���� �� �����
    * ���������� �ϱ� ���ؼ� 1-base�� ����
    */
    line.resize(k + 1);
    for (int i = 1; i <= k; i++) {
        line_out_pq.push(pint(0, i));
    }
    
    /*
    * ���ʴ�� ������ ����� ���� �� ����
    * line_out_pq�� top()�� ���� �����ϴ� ���� ���� ����
    * �ش� ��ȣ�� ť�� �����ϰ�, line_out_pq ������Ʈ
    */
    for (int i = 0, c_id, itm; i < n; i++) {
        cin >> c_id >> itm;

        int base_time = line_out_pq.top().first;
        int line_idx = line_out_pq.top().second;
        line_out_pq.pop();

        line[line_idx].push(pint(c_id, base_time + itm));
        line_out_pq.push(pint(base_time + itm, line_idx));
    }

    /*
    * total_out_pq �ʱ�ȭ
    * �� ������ ù ��° �� ����� total_out_pq�� ����
    */
    for (int i = 1; i <= k; i++) {
        if (!line[i].empty()) {
            total_out_pq.push(pq_n(i, line[i].front().second, line[i].front().first));
            line[i].pop();
        }
    }

    /*
    * 1������ n���� ����� ��� üũ
    * ���� ������ ����� ���� �� ��ȣ�� �����ͼ�
    * �� �ٿ��� ��� ���� ����� ���� push
    * ����� n�� ������ n���� �ݺ��ϸ� �ȴ�.
    */
    for (lli i = 1; i <= n; i++) {
        int c_id = total_out_pq.top().cus_id;
        int cur_line = total_out_pq.top().line_n;
        total_out_pq.pop();

        res += c_id * i;
        if (!line[cur_line].empty()) {
            int new_cus_id = line[cur_line].front().first;
            int new_out_time = line[cur_line].front().second;
            line[cur_line].pop();

            total_out_pq.push(pq_n(cur_line, new_out_time, new_cus_id));
        }
    }

    cout << res;

    return 0;
}