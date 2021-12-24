#include <iostream>

using namespace std;

int n;
int dist[20][20];
bool usable[20][20];

bool floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && i != k && j != k) {
                    if (dist[i][j] == dist[i][k] + dist[k][j]) {
                        usable[i][j] = false;
                    }
                    else if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
            usable[i][j] = true;
        }
    }

    /*
    * 플로이드-와샬 알고리즘을 수행하면서, 사용 가능한 간선인지 체크.
    * 중간에 모순이 발생하면 -1을 출력한다. 없다면, 사용 가능한 간선의
    * 가중치를 모두 더한 후 출력.
    */
    if (floyd()) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (usable[i][j]) {
                    sum += dist[i][j];
                }
            }
        }
        cout << sum;
    }
    else {
        cout << -1;
    }

    return 0;
}