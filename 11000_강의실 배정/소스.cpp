#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

int n, min_class = 0;
vector<pint> time_set;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    time_set.resize(n);
    for (pint& p : time_set) {
        cin >> p.first >> p.second;
    }
    sort(time_set.begin(), time_set.end());

    /*
    * 시작 시간 순으로 시간을 정렬한 후, 끝나는 시간을 확인.
    * 우선순위 큐에는 수업의 끝나는 시간을 오름차순으로 삽입.
    * 우선순위 큐의 크기가 사용할 방의 갯수이다.
    * 만약 우선순위 큐가 비어있다면, 바로 현재 보고있는 수업의 끝나는 시간 삽입.
    * 만약 큐의 최저값이 현재 수업의 시작 시간보다 작다면, 같은 방에서 할 수 있음.
    * 그러므로 큐에서 pop하고, 현재 수업의 끝나는 시간 삽입.
    * 아니라면, 같은 방에서 수업할 수 없음. 그러므로 바로 끝나는 시간 삽입.
    */
    for (int i = 0; i < n; i++) {
        if (pq.empty()) {
            pq.push(time_set[i].second);
        }
        else {
            if (time_set[i].first >= pq.top()) {
                pq.pop();
            }

            pq.push(time_set[i].second);
        }

        min_class = max<int>(min_class, pq.size());
    }

    cout << min_class;

    return 0;
}