#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

const int NOT_VISIT = -1;

int n, m;
int dst[101];
int dist[101];
queue<int> que;

int main() {
    /*
    * bfs를 통해 100개의 칸을 탐색한다. 현재 칸의 번호와 주사위 번호의 합이 100을
    * 초과하면 탐색하지 않는다. 만약 도착한 칸에 뱀이나 사다리가 있다면, 반드시
    * 그 기물을 사용해야 하므로 각 탐색마다 해당 칸에 기물이 있는지를 확인한다.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    fill(dist + 1, dist + 101, NOT_VISIT);
    iota(dst + 1, dst + 101, 1);
    cin >> n >> m;
    for(int i = 0, from, to; i < n + m; i++) {
        cin >> from >> to;
        dst[from] = to;
    }

    dist[dst[1]] = 0;
    que.push(dst[1]);
    while(!que.empty()) {
        int cur = que.front();
        que.pop();

        for(int i = 1; i <= 6; i++) {
            if(cur + i <= 100 && dist[dst[cur + i]] == NOT_VISIT) {
                dist[dst[cur + i]] = dist[cur] + 1;
                que.push(dst[cur + i]);
            }
        }
    }

    cout << dist[100];

    return 0;
}