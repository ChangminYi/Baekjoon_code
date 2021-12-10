#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

typedef pair<int, vector<int>> dat;

const int MAX = 51;

int n;
vector<int> graph[MAX];
queue<int> que;

int bfs(const int start) {
    int ret = 0;
    int dist[MAX] = { 0 };
    bool visit[MAX] = { false };

    visit[start] = true;
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        ret = max(ret, dist[cur]);
        que.pop();

        for (const int& nxt : graph[cur]) {
            if (!visit[nxt]) {
                dist[nxt] = dist[cur] + 1;
                visit[nxt] = true;
                que.push(nxt);
            }
        }
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int n1, n2; ; ) {
        cin >> n1 >> n2;

        if (n1 == -1 && n2 == -1) {
            break;
        }
        else {
            graph[n1].push_back(n2);
            graph[n2].push_back(n1);
        }
    }

    /*
    * 각 노드를 시작점으로 하여 bfs를 실행.
    * 이 때, 최대거리가 최소인 노드들을 구하여 출력하면 된다.
    */
    int min_dist = INT32_MAX;
    vector<int> candidate;
    for (int i = 1, tmp_dist; i <= n; i++) {
        tmp_dist = bfs(i);

        if (tmp_dist == min_dist) {
            candidate.push_back(i);
        }
        else if (tmp_dist < min_dist) {
            min_dist = tmp_dist;
            candidate = vector<int>(1, i);
        }
    }

    cout << min_dist << ' ' << candidate.size() << '\n';
    for (const int& i : candidate) {
        cout << i << ' ';
    }

    return 0;
}