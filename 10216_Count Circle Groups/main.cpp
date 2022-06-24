#include <iostream>
#include <cmath>

using namespace std;

int t, n;
int dir[3000][2], r[3000], par[3000];

double get_dist(int i, int j) {
    int x_diff = dir[i][0] - dir[j][0];
    int y_diff = dir[i][1] - dir[j][1];
    return sqrt(x_diff * x_diff + y_diff * y_diff);
}

int find_par(const int x) {
    if(par[x] == x) return x;
    else return par[x] = find_par(par[x]);
}

void union_set(const int x, const int y) {
    par[find_par(x)] = find_par(y);
}

int main() {
    /**
     * union-find로 연결된 진영의 집합을 구할 수 있음. 
     * 초기에 집합은 n개이고, 연결이 확인될 때마다 1개씩
     * 줄여 나가다 보면 마지막에 전체 집합의 수가 남음.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    do {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> dir[i][0] >> dir[i][1] >> r[i];
            par[i] = i;
        }

        int ans = n;
        for(int i = 0; i < n - 1; i++) {
            for(int j = i + 1; j < n; j++) {
                if(get_dist(i, j) <= r[i] + r[j] && find_par(i) != find_par(j)) {
                    union_set(i, j);
                    ans--;
                }
            }
        }

        cout << ans << '\n';
    } while(--t);

    return 0;
}