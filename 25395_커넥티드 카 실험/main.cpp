#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

int n, s;
int x[1000000], h[1000000];
bool visit[1000000];
queue<int> que;

int main() {
    /**
     * bfs를 사용하여 연결된 차들을 탐색할 수 있다.
     * 선형탐색을 하면 시간이 오래 걸리므로, 새로 갱신되는 최대/최저점에 대하여
     * 이분탐색을 실행한다. 새로운 최대/최저를 찾으면, 아직 탐색하지 않은 모든
     * 노드를 큐에 삽입하여 탐색을 계속한다. 그 후 방문한 모든 노드의 번호를 출력한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> s;
    for(int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> h[i];
    }

    int lb = x[s - 1], hb = x[s - 1];
    visit[s - 1] = true;
    que.push(s - 1);
    while(!que.empty()) {
        int cur = que.front();
        que.pop();

        int new_lb = x[cur] - h[cur];
        if(new_lb < lb) {
            int lo = lower_bound(x, x + n, new_lb) - x;
            while(lo < cur) {
                if(visit[lo]) break;
                visit[lo] = true;
                que.push(lo++);
            }
            lb = new_lb;
        }

        int new_hb = x[cur] + h[cur];
        if(hb < new_hb) {
            int hi = upper_bound(x, x + n, new_hb) - x - 1;
            while(hi > cur) {
                if(visit[hi]) break;
                visit[hi] = true;
                que.push(hi--);
            }
            hb = new_hb;
        }
    }

    for(int i = 0; i < n; i++) {
        if(visit[i]) cout << i + 1 << ' ';
    }

    return 0;
}