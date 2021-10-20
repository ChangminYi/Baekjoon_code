#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef pair<int, int> pint;

int n, m;
set<int> elem;
vector<vector<pint>> graph;
vector<vector<int>> dp;
vector<int> degree;
queue<int> que;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n + 1);
    degree.resize(n + 1, 0);

    for (int i = 0, x, y, k; i < m; i++) {
        cin >> x >> y >> k;

        degree[x]++;
        graph[y].push_back(pint(x, k));
    }

    /*
    * degree�� 0�̶�� �⺻ ��ǰ�̹Ƿ�, ť�� �����ϰ�
    * �⺻ ��ǰ ��Ͽ� �ø���.
    */
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) {
            que.push(i);
            elem.insert(i);
        }
    }

    /*
    * dp���̺� �ʱ�ȭ. column�� ũ��� �⺻ ��ǰ�� ��
    */
    dp.resize(n + 1, vector<int>(elem.size(), 0));
    for (auto i = elem.begin(); i != elem.end(); i++) {
        dp[*i][distance(elem.begin(), i)] = 1;
    }

    /*
    * ���� ���ķ� ��ǰ �� ����
    * ����� ���� ��ǰ�� �ڽ��� ��ǰ �� * �ʿ� ���� ��� ���Ѵ�.
    * degree�� 0�� �Ǹ� ť�� �����Ͽ� �ݺ�.
    */
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const pint& edge : graph[cur]) {
            int nxt = edge.first;

            for (int i = 0; i < (int)elem.size(); i++) {
                dp[nxt][i] += dp[cur][i] * edge.second;
            }

            if (--degree[nxt] == 0) {
                que.push(nxt);
            }
        }
    }

    for (auto i = elem.begin(); i != elem.end(); i++) {
        cout << *i << ' ' << dp[n][distance(elem.begin(), i)] << '\n';
    }

    return 0;
}