#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

const int INF = INT32_MAX / 2;

struct pqn {
    int node, dist;
    pqn(const int _n, const int _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) {
        return this->dist > other.dist;
    }
};

int n, t, m;
bool is_spc[1001];
int dir[1001][2], weight[1001][1001], dist[1001][1001];
priority_queue<pqn, vector<pqn>, greater<>> pq;

void init_weight() {
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (is_spc[i] && is_spc[j]) {
                weight[i][j] = min(abs(dir[i][0] - dir[j][0]) + abs(dir[i][1] - dir[j][1]), t);
            }
            else {
                weight[i][j] = abs(dir[i][0] - dir[j][0]) + abs(dir[i][1] - dir[j][1]);
            }
            weight[j][i] = weight[i][j];
        }
    }
}

void dijk(const int start) {
    fill(dist[start] + 1, dist[start] + n + 1, INF);

    dist[start][start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (int i = 1, new_dist; i <= n; i++) {
                new_dist = cur_dist + weight[cur][i];
                if (i != cur && new_dist < dist[start][i]) {
                    dist[start][i] = new_dist;
                    pq.push(pqn(i, new_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> t;
    for (int i = 1, s; i <= n; i++) {
        cin >> s >> dir[i][0] >> dir[i][1];
        is_spc[i] = (s == 1);
    }

    init_weight();
    for (int i = 1; i <= n; i++) {
        dijk(i);
    }

    cin >> m;
    for (int a, b; m > 0; m--) {
        cin >> a >> b;
        cout << dist[a][b] << '\n';
    }

    return 0;
}