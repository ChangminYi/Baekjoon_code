#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int usado, node;
    edge(const int _n = 0, const int _u = 0) : node(_n), usado(_u) {}
};

int n, q;
int usado[5'001];
bool visit[5'001];
vector<edge> tree[5'001];
queue<int> que;

int bfs(const int start, const int base) {
    int ret = 0;
    fill(visit + 1, visit + n + 1, false);

    visit[start] = true;
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const edge& e : tree[cur]) {
            if (!visit[e.node] && e.usado >= base) {
                visit[e.node] = true;
                ret++;
                que.push(e.node);
            }
        }
    }

    return ret;
}

int main() {
    /*
    * ��Ʈ��ũ�� Ʈ�� �����̱� ������, �ܼ� bfs�� �ذ� �����ϴ�.
    * ������ usado�� k �̸��̸� �� ��ο����� Ž���� �ߴ��Ѵ�.
    * �������� ������, bfs�� �湮�� ����� ���� ����ϸ� �ȴ�.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> q;
    for (int i = 0, p, q, r; i < n - 1; i++) {
        cin >> p >> q >> r;
        tree[p].push_back(edge(q, r));
        tree[q].push_back(edge(p, r));
    }

    for (int k, v; q; q--) {
        cin >> k >> v;
        cout << bfs(v, k) << '\n';
    }

    return 0;
}