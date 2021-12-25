#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>
#include <string>

using namespace std;

typedef pair<int, int> pint;

const int INF = INT32_MAX / 2;

int n, d;
string tmp;
vector<int> graph[50];
int dist[50][50];

void dijk(int start) {
    priority_queue<pint, vector<pint>, greater<pint>> pq;

    dist[start][start] = 0;
    pq.push(pint(0, start));
    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (const int nxt : graph[cur]) {
                int new_dist = cur_dist + 1;
                if (new_dist < dist[start][nxt]) {
                    dist[start][nxt] = new_dist;
                    pq.push(pint(new_dist, nxt));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        for (int j = 0; j < n; j++) {
            if (tmp[j] == 'Y') {
                graph[i].push_back(j);
            }
        }
    }

    /*
    * 각 노드 간의 거리를 1로 가정하고, 노드 간의 최대 거리를 구한다.
    * 만약 갈 수 없는 노드가 있다면, 차이가 무한대가 된다. 따라서 -1을 출력한다.
    * 아니라면, 거리 * d의 값이 최대 차이이므로 이 값을 출력하면 된다.
    */
    for (int i = 0; i < n; i++) {
        fill(dist[i], dist[i] + n, INF);
        dijk(i);
    }

    int max_dist = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            max_dist = max(max_dist, dist[i][j]);
        }
    }

    cout << (max_dist == INF ? -1 : d * max_dist);

    return 0;
}