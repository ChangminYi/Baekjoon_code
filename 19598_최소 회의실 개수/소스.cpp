#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
vector<pint> times;

bool do_allocate(const int size) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < size; i++) {
        pq.push(0);
    }

    for (int i = 0; i < n; i++) {
        if (times[i].first >= pq.top()) {
            pq.pop();
            pq.push(times[i].second);
        }
        else {
            return false;
        }
    }

    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0, stt, fin; i < n; i++) {
        cin >> stt >> fin;
        times.push_back(pint(stt, fin));
    }

    sort(times.begin(), times.end());

    /*
    * 회의를 시작하는 시간 순서로 정렬한 다음, 회의실의 수를 매개변수로 이분탐색한다.
    * 회의실은 우선순위 큐에서 초기 원소의 수로 표현한다.
    */
    int ans = 0;
    int lo = 1, hi = n;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        if (do_allocate(mid)) {
            ans = mid;
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << ans;

    return 0;
}