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
    * 일단 낮은 번호의 계산대부터 한 명씩 넣는다.
    * n명을 다 넣었으면 break한다.
    * 그리고 빠져나가는 순서를 pq에 넣는다.
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
    * 아직 계산대에 들어가지 못한 사람이 남아있는 경우.
    * 먼저 사람이 빠져나가는 계산대에 다음 사람은 넣는다.
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
    * 나가는 순서를 정한다.
    * 각 계산대에서 첫 번째로 계산을 마치는 사람들을 저장.
    * 만약 최대 인원 넘어가면 끝낸다.
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
    * 결과 값 계산 및 남은 사람 다시 pq에 넣기
    * 결과값에 넣은 사람의 줄 번호에 아직 사람이 남아있으면
    * 그 사람을 pq에 넣어서 끝날 때까지 계산한다.
    * 오버플로우 조심
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