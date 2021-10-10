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
    * 사용 가능한 계산대 줄 만들기
    * 직관적으로 하기 위해서 1-base로 설정
    */
    line.resize(k + 1);
    for (int i = 1; i <= k; i++) {
        line_out_pq.push(pint(0, i));
    }
    
    /*
    * 차례대로 들어오는 사람의 계산대 줄 설정
    * line_out_pq의 top()은 조건 만족하는 가장 빠른 계산대
    * 해당 번호의 큐에 저장하고, line_out_pq 업데이트
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
    * total_out_pq 초기화
    * 각 계산대의 첫 번째 줄 사람들 total_out_pq에 삽입
    */
    for (int i = 1; i <= k; i++) {
        if (!line[i].empty()) {
            total_out_pq.push(pq_n(i, line[i].front().second, line[i].front().first));
            line[i].pop();
        }
    }

    /*
    * 1번부터 n번의 사람들 모두 체크
    * 현재 나가는 사람의 계산대 줄 번호를 가져와서
    * 그 줄에서 계산 끝난 사람의 정보 push
    * 사람이 n명 있으니 n번만 반복하면 된다.
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