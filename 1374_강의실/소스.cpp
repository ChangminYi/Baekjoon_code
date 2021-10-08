#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n, tmp;
size_t max_size = 0;
vector<pint> argi;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    
    argi.resize(n);
    for (pint& p : argi) {
        cin >> tmp >> p.first >> p.second;
    }

    /*
    * 모든 강의를 시작 시간순으로 정렬하고, 스위핑을 한다. 
    * 현재 강의의 시작 시간보다 작거나 같은 모든 강의를 없애고,
    * 현재 강의의 끝나는 시간을 pq에 넣는다.
    * 최대 필요한 강의실 수는 pq의 최대 크기와 같다.
    */
    sort(argi.begin(), argi.end());
    for (const pint& p : argi) {
        while (!pq.empty() && pq.top() <= p.first) {
            pq.pop();
        }
        pq.push(p.second);

        max_size = max(max_size, pq.size());
    }

    cout << max_size;

    return 0;
}