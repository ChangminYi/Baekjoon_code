#include <iostream>
#include <queue>

using namespace std;

int n, k;
priority_queue<int> pq;

int main() {
    long long sum = 0;
    int back_tmp, cur_tmp;
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 인접한 사람과의 키 차이가 가장 많이 나는 구간마다 끊으면,
    * 총 비용을 최소로 줄일 수 있다. 따라서, 두 값의 차이를 모두
    * 저장한 후 정렬하여 가장 큰 값 k-1개를 버리면 k개의 구간으로
    * 끊은 것과 같다. 그 후, 남은 차이를 모두 더하면 된다.
    */
    cin >> n >> k;
    cin >> back_tmp;
    for (int i = 1; i < n; i++) {
        cin >> cur_tmp;
        pq.push(cur_tmp - back_tmp);
        back_tmp = cur_tmp;
    }

    for (int i = 0; i < n - 1; i++) {
        if (i >= k - 1) {
            sum += pq.top();
        }
        pq.pop();
    }

    cout << sum;

    return 0;
}