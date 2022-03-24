#include <iostream>
#include <queue>
#include <cmath>
#include <functional>

using namespace std;

struct dat {
    int val, idx;
    dat(int _v = 0, int _i = 0) : val(_v), idx(_i) {}
    bool operator>(const dat& other) const { return val > other.val; }
};

int n, l, base;
priority_queue<dat, vector<dat>, greater<>> pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 우선순위 큐를 오름차순으로 설정한다. 값을 인덱스와 같이 삽입하여
    * 범위에 맞지 않는 최솟값이 top이라면 pop한다. 그리고 현재 인덱스의
    * 값을 삽입한 다음, top의 값을 출력하면 된다.
    */

    cin >> n >> l;
    for (int i = 1, val; i <= n; i++) {
        cin >> val;
        
        base = max(1, i - l + 1);
        while (!pq.empty() && pq.top().idx < base) {
            pq.pop();
        }
        pq.push(dat(val, i));

        cout << pq.top().val << ' ';
    }

    return 0;
}