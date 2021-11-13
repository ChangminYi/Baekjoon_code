#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;

const int INF = INT32_MAX / 2;

int n, k;
vector<vector<int>> weight, dist;
vector<int> perm;
priority_queue<pint, vector<pint>, greater<pint>> pq;

void dijk(int start) {
    dist[start][start] = 0;
    pq.push(pint(0, start));

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (int i = 0, new_dist; i < n; i++) {
                new_dist = cur_dist + weight[cur][i];

                if (new_dist < dist[start][i]) {
                    dist[start][i] = new_dist;
                    pq.push(pint(dist[start][i], i));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;

    weight.resize(n, vector<int>(n));
    dist.resize(n, vector<int>(n, INF));

    for (vector<int>& row : weight) {
        for (int& i : row) {
            cin >> i;
        }
    }

    // 플로이드-와샬 대신 다익스트라를 n번 실행
    for (int i = 0; i < n; i++) {
        dijk(i);
    }

    // 방문 순열 초기화. 가장 앞에 시작점을 놓고, 그 다음부터는 오름차순
    perm.push_back(k);
    for (int i = 0; i < n; i++) {
        if (i != k) {
            perm.push_back(i);
        }
    }

    /*
    * 브루트포스로 모든 경우의 수 계산.
    * 시작점을 제외한 모든 점의 순서를 계산하여
    * 그 순서에 따른 최종 거리 계산 및 최솟값 구하기.
    */
    int res = INF;
    do {
        int dist_sum = 0;
        for (int i = 0; i < n - 1; i++) {
            dist_sum += dist[perm[i]][perm[i + 1]];
        }
        res = min(res, dist_sum);
    } while (next_permutation(perm.begin() + 1, perm.end()));

    cout << res;

    return 0;
}