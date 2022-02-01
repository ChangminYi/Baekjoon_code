#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const long long INF = INT64_MAX / 2;

int n, s, e, m;
vector<int> adj[50];
int cycle[50];
long long weight[50][50] = {INF}, dist[50], earn[50];
bool has_cycle = false, in_que[50], visit[50], poss[50];
queue<int> que, cycle_que;

void spfa() {
    fill(dist, dist + n, INF);

    dist[s] = -earn[s];
    in_que[s] = true;
    que.push(s);
    while (!que.empty()) {
        int cur = que.front();
        in_que[cur] = false;
        que.pop();

        for (const int& nxt : adj[cur]) {
            long long new_dist = dist[cur] + weight[cur][nxt] - earn[nxt];
            if (new_dist < dist[nxt]) {
                dist[nxt] = new_dist;

                if (!in_que[nxt]) {
                    if (++cycle[nxt] < n) {
                        in_que[nxt] = true;
                        que.push(nxt);
                    }
                    else {
                        has_cycle = true;
                        if (!visit[nxt]) {
                            visit[nxt] = true;
                            cycle_que.push(nxt);
                        }
                    }
                }
            }
        }
    }
}

void init_poss() {
    que.push(s);
    poss[s] = true;
    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        for (const int& nxt : adj[cur]) {
            if (!poss[nxt]) {
                poss[nxt] = true;
                que.push(nxt);
            }
        }
    }
}

void cycle_bfs() {
    while (!cycle_que.empty()) {
        int cur = cycle_que.front();
        cycle_que.pop();
        for (const int& nxt : adj[cur]) {
            if (!visit[nxt]) {
                visit[nxt] = true;
                cycle_que.push(nxt);
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 상당히 고려해야 할 것이 많다. 일단, 간선이 유일하게 주어지지 않는다.
    * 최소 가중치로 간선의 값을 초기화하면, bfs를 통해 목적지에 갈 수 있는지 확인한다.
    * 만약 갈 수 있다면, spfa 알고리즘이나 벨만-포드 알고리즘으로 최단거리 및 사이클 유무 업데이트.
    * 사이클이 있고 목적지가 사이클에서 도달 가능하면 무한히 돈을 많이 벌 수 있음.
    * 사이클이 있지만 목적지에 도달 불가능하면 유한한 돈을 벌 수 있다. 이를 유의하여 출력하면 된다.
    */
    cin >> n >> s >> e >> m;
    for (int i = 0; i < n; i++) {
        fill(weight[i], weight[i] + n, INF);
    }
    for (int i = 0, from, to, w; i < m; i++) {
        cin >> from >> to >> w;
        adj[from].push_back(to);
        weight[from][to] = min<long long>(weight[from][to], w);
    }
    for (int i = 0; i < n; i++) {
        cin >> earn[i];
    }

    init_poss();

    if (!poss[e]) {
        cout << "gg";
    }
    else {
        spfa();
        cycle_bfs();
        if (has_cycle && visit[e]) {
            cout << "Gee";
        }
        else {
            cout << -dist[e];
        }
    }

    return 0;
}