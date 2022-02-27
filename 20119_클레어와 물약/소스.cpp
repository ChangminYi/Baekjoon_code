#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

int n, m, l;
int buf[200'000];
bool visit[200'001];
vector<int> degree[200'001];
vector<pint> graph[200'001];
queue<int> que;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 한 물약을 만드는 방법이 여러 개 존재할 수 있다.
    * 따라서, 모든 레시피를 구분하기 위해서 degree를 2차원으로 설정하고,
    * 그래프의 간선을 노드 번호와 degree의 인덱스로 구성한다.
    * 위상 정렬을 실행할 때는 노드 번호만을 사용하여 정렬하면 된다.
    */

    cin >> n >> m;
    for (int k, r; m; m--) {
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> buf[i];
        }
        cin >> r;
        degree[r].push_back(k);
        for (int i = 0; i < k; i++) {
            graph[buf[i]].push_back(pint(r, degree[r].size() - 1));
        }
    }
    cin >> l;
    for (int i = 0, tmp; i < l; i++) {
        cin >> tmp;
        que.push(tmp);
        visit[tmp] = true;
    }

    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const pint& edge : graph[cur]) {
            if (--degree[edge.first][edge.second] == 0 && !visit[edge.first]) {
                visit[edge.first] = true;
                l++;
                que.push(edge.first);
            }
        }
    }

    cout << l << '\n';
    for (int i = 1; i <= n; i++) {
        if (visit[i]) cout << i << ' ';
    }

    return 0;
}