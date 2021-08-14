#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int testcase;
int n, m;
vector<int> order, degree;
vector<vector<bool>> adj_mtx;
queue<int> que;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    do {
        cin >> n;
        order = vector<int>(n);
        degree = vector<int>(n + 1, 0);
        adj_mtx = vector<vector<bool>>(n + 1, vector<bool>(n + 1, false));
        
        for (int& i : order) {
            cin >> i;
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                adj_mtx[order[i]][order[j]] = true;
                degree[order[j]]++;
            }
        }

        cin >> m;
        for (int i = 0, arg1, arg2; i < m; i++) {
            cin >> arg1 >> arg2;
            if (adj_mtx[arg1][arg2]) {
                adj_mtx[arg1][arg2] = false;
                adj_mtx[arg2][arg1] = true;
                degree[arg2]--, degree[arg1]++;
            }
            else {
                adj_mtx[arg2][arg1] = false;
                adj_mtx[arg1][arg2] = true;
                degree[arg1]--, degree[arg2]++;
            }
        }

        for (int i = 1; i <= n; i++) {
            if (degree[i] == 0) {
                que.push(i);
            }
        }

        vector<int> res;
        bool not_unique = false;
        while (!que.empty()) {
            if (que.size() > 1) {
                not_unique = true;
                break;
            }
            else {
                int cur = que.front();
                que.pop();
                res.push_back(cur);

                for (int i = 1; i <= n; i++) {
                    if (adj_mtx[cur][i] && --degree[i] == 0) {
                        que.push(i);
                    }
                }
            }
        }

        if (not_unique) {
            cout << "?\n";
        }
        else{
            if (res.size() == n) {
                for (const int& i : res) {
                    cout << i << ' ';
                }
                cout << '\n';
            }
            else {
                cout << "IMPOSSIBLE\n";
            }
        }
    } while (--testcase > 0);

    return 0;
}