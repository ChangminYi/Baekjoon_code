#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int NOT_VISIT = -1;

int n, l, start, dest;
vector<int> graph[200001];
int dist[200001];
queue<int> que;

int bfs() {
    fill(dist, dist + 2 * n + 1, NOT_VISIT);

    dist[start] = 0;
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        if (cur == dest) {
            return dist[cur] > 1 ? dist[cur] - 1 : 0;
        }
        else {
            for (const int nxt : graph[cur]) {
                if (dist[nxt] == NOT_VISIT) {
                    dist[nxt] = dist[cur] + (nxt > n ? 1 : 0);
                    que.push(nxt);
                }
            }
        }
    }

    return -1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� ��带 ����Ͽ� ȯ���� ǥ��. ȯ���� ��� �Ÿ��� 1 �þ��,
    * �ƴϸ� ���� �Ÿ��� ���� �����Ѵ�. bfs�� ���� �Ÿ��� ���ϰ�, ����Ѵ�.
    */
    cin >> n >> l;
    for (int i = 1, node; i <= l; i++) {
        while (true) {
            cin >> node;

            if (node == -1) {
                break;
            }
            else{
                graph[node].push_back(n + i);
                graph[n + i].push_back(node);
            }
        }
    }
    cin >> start >> dest;

    cout << bfs();

    return 0;
}