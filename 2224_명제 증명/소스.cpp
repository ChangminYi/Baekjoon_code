#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>
#include <cctype>

using namespace std;

struct pqn {
    int node = 0, dist = 0;
    pqn(const int _n, const int _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const {
        return this->dist > other.dist;
    }
};
typedef pair<int, int> pint;

const int INF = INT32_MAX / 2;
const int SIZE = 52;

int x;
vector<int> graph[52];
int dist[52][52];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

int get_idx(const char c) {
    return (isupper(c) ? c - 'A' : c - 'a' + SIZE / 2);
}

char get_char(const int i) {
    return (i < SIZE / 2 ? 'A' + i : 'a' + i - SIZE / 2);
}

void dijk(const int start) {
    fill(dist[start], dist[start] + SIZE, INF);

    dist[start][start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (const int nxt : graph[cur]) {
                int new_dist = cur_dist + 1;
                if (new_dist < dist[start][nxt]) {
                    dist[start][nxt] = new_dist;
                    pq.push(pqn(nxt, new_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    (cin >> x).ignore();
    for (string tmp; x > 0; x--) {
        getline(cin, tmp);
        char from = tmp.front(), to = tmp.back();
        graph[get_idx(from)].push_back(get_idx(to));
    }

    for (int i = 0; i < SIZE; i++) {
        dijk(i);
    }

    /*
    * 명제를 유향 그래프에 매핑하여 모든 노드에서의 최단거리 구함.
    * i에서 j로 연결되어 있다면 연쇄적으로 증명이 가능한 노드.
    * 이를 모두 찾아 출력하면 된다.
    */
    int cnt = 0;
    vector<pint> ans;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i != j && dist[i][j] != INF) {
                cnt++;
                ans.push_back(pint(i, j));
            }
        }
    }
    cout << cnt << '\n';
    for (const pint& p : ans) {
        cout << get_char(p.first) << " => " << get_char(p.second) << '\n';
    }

    return 0;
}