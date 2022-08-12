#include <iostream>
#include <cmath>

using namespace std;

const int INF = INT32_MAX / 2;

int n, q, c, s, e;
int dist[301][301][301];

int main() {
    /**
     * 플로이드 와샬 알고리즘을 사용하여 최단거리를 구하면서,
     * 그 중간 과정을 모두 저장해야 한다. 2^C 이상의 방울을 마실 수
     * 없다는 말은 C - 1번 노드까지만을 사용하면서 이동해야 함을 뜻한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> dist[i][j][0];
            if(i != j && dist[i][j][0] == 0) dist[i][j][0] = INF;
        }
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                dist[i][j][k] = min(dist[i][j][k - 1], dist[i][k][k - 1] + dist[k][j][k - 1]);
            }
        }
    }

    do {
        cin >> c >> s >> e;
        cout << (dist[s][e][c - 1] == INF ? -1 : dist[s][e][c - 1]) << '\n';
    } while(--q);

    return 0;
}
