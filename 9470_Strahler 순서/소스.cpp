#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int testcase;
int k, m, p;
vector<vector<int>> graph;
vector<vector<int>> child;
vector<int> degree, order;
queue<int> que;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� ������ ���� �ڽź��� �տ� �ִ� ������ ������ ���� ���ϰ�,
    * ���ǿ� ���� �ڽ��� ������ ���� �� ������ ����� ������ ���.
    */
    cin >> testcase;
    do {
        cin >> k >> m >> p;
        graph = vector<vector<int>>(m + 1);
        child = vector<vector<int>>(m + 1);
        degree = vector<int>(m + 1, 0);
        order = vector<int>(m + 1);

        for (int i = 0, from, to; i < p; i++) {
            cin >> from >> to;
            graph[from].push_back(to);
            child[to].push_back(from);
            degree[to]++;
        }

        for (int i = 1; i <= m; i++) {
            if (degree[i] == 0) {
                que.push(i);
            }
        }
        while (!que.empty()) {
            int cur = que.front();
            que.pop();

            int cur_order;
            if (child[cur].empty()) {
                cur_order = 1;
            }
            else {
                int max_val = 0, same_cnt = 0;
                for (const int chd : child[cur]) {
                    if (max_val < order[chd]) {
                        max_val = order[chd];
                        same_cnt = 1;
                    }
                    else if (max_val == order[chd]) {
                        same_cnt++;
                    }
                }

                cur_order = (same_cnt == 1 ? max_val : max_val + 1);
            }
            order[cur] = cur_order;

            for (const int nxt : graph[cur]) {
                if (--degree[nxt] == 0) {
                    que.push(nxt);
                }
            }
        }

        cout << k << ' ' << order[m] << '\n';
    } while (--testcase);

    return 0;
}