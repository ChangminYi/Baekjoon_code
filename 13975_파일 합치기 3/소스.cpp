#include <iostream>
#include <queue>
#include <functional>

using namespace std;

typedef long long lli;

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    priority_queue<lli, vector<lli>, greater<lli>> pq;
    int iter;
    cin >> iter;

    while (iter-- > 0) {
        int n;
        cin >> n;

        for (int i = 0; i < n; i++) {
            lli temp;
            cin >> temp;
            pq.push(temp);
        }

        lli sumation = 0;
        while (pq.size() > 1) {
            lli frt = pq.top();
            pq.pop();
            lli bck = pq.top();
            pq.pop();

            sumation += frt + bck;
            pq.push(frt + bck);
        }

        cout << sumation << '\n';
        while (!pq.empty()) {
            pq.pop();
        }
    }

    return 0;
}