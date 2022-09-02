#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

int t, n, m;
int person[100000];
pint car[100000];

int main() {
    /**
     * 그리디하게 접근한다. 가까운 승객부터 보내기 시작하는데,
     * 운전자 중 승객을 태울 수 있으면서 z가 작은 운전자를 먼저 매칭한다.
     * 이를 반복하면 최대한 많은 매칭을 할 수 있다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    do {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
            cin >> person[i];
        for(int i = 0; i < m; i++)
            cin >> car[i].first >> car[i].second;

        sort(person, person + n);
        sort(car, car + m);

        int cnt = 0;
        priority_queue<int, vector<int>, greater<>> pq;
        for(int i = 0, j = 0; i < n; i++) {
            for(; j < m && car[j].first <= person[i]; j++)
                pq.push(car[j].second);

            while(!pq.empty() && pq.top() < person[i])
                pq.pop();
            
            if(!pq.empty())
                cnt++, pq.pop();
        }

        cout << cnt << '\n';
    } while(--t);

    return 0;
}