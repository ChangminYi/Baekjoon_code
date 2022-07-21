#include <iostream>
#include <queue>

using namespace std;

struct pcb {
    int pid, pri, time;
    pcb(const int _pid, const int _pri, const int _t): pid(_pid), pri(_pri), time(_t) {}
    bool operator<(const pcb& other) const {
        if(pri != other.pri) return pri < other.pri;
        else return pid > other.pid;
    }
};

int n, t;
priority_queue<pcb> pq;

int main() {
    /**
     * 나머지 프로세스들의 우선순위를 모두 1 올리는 것은 비효율적이다.
     * 반대로, 현재 프로세스의 우선순위를 1 내려도 결과는 동일하다.
     * 실행시간이 1 남았다면, 현재 실행 후 다시 실행할 필요가 없다.
     * 이를 토대로 우선순위 큐를 사용하여 구현하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t >> n;
    for(int pid, pri, t; n; n--) {
        cin >> pid >> t >> pri;
        pq.push(pcb(pid, pri, t));
    }

    while(t--) {
        pcb cur = pq.top();
        pq.pop();

        cout << cur.pid << '\n';
        if(cur.time > 1) pq.push(pcb(cur.pid, cur.pri - 1, cur.time - 1));
    }

    return 0;
}