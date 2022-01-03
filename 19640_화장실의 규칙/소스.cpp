#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct person {
    int d = 0, h = 0, init_num = 0;
    person(int _d, int _h, int _i) : d(_d), h(_h), init_num(_i) {}
};

struct line_node {
    int idx = 0;
    line_node(int _idx) : idx(_idx) {}
};

int n, m, k;
vector<queue<person>> lines;
priority_queue<line_node> pq;

bool operator<(const line_node& lhs, const line_node& rhs) {
    if (lines[lhs.idx].front().d != lines[rhs.idx].front().d) {
        return lines[lhs.idx].front().d < lines[rhs.idx].front().d;
    }
    else if (lines[lhs.idx].front().h != lines[rhs.idx].front().h) {
        return lines[lhs.idx].front().h < lines[rhs.idx].front().h;
    }
    else {
        return lhs.idx > rhs.idx;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * m개의 큐에 사람의 정보를 넣어준다. 그리고 조건에 맞게 비교 함수를 구현한다.
    * 우선순위 큐에는 인덱스만 삽입한다. 만약 우선순위 큐의 top이 가리키는 큐의
    * front가 k번째 사람일 경우, 결과를 출력한다. 아니라면, 큐의 front를 pop하고,
    * 큐가 비어있지 않다면 다시 인덱스를 우선순위 큐에 삽입한다.
    */
    cin >> n >> m >> k;
    lines.resize(m);
    for (int i = 0, tmp_d, tmp_h; i < n; i++) {
        cin >> tmp_d >> tmp_h;
        lines[i % m].push(person(tmp_d, tmp_h, i));
    }

    for (int i = 0; i < m; i++) {
        if (!lines[i].empty()) {
            pq.push(line_node(i));
        }
    }

    int cnt = 0;
    while (!pq.empty()) {
        int cur_idx = pq.top().idx;
        pq.pop();

        if (lines[cur_idx].front().init_num == k) {
            break;
        }
        else {
            cnt++;
            lines[cur_idx].pop();
            if (!lines[cur_idx].empty()) {
                pq.push(line_node(cur_idx));
            }
        }
    }

    cout << cnt;

    return 0;
}