#include <iostream>
#include <vector>

using namespace std;

int n;
bool visit[100'001];
vector<int> graph[100'001];

pair<int, int> dfs(const int cur, const int dist) {
    pair<int, int> ret(cur, dist);

    for (const int& nxt : graph[cur]) {
        if (!visit[nxt]) {
            visit[nxt] = true;
            pair<int, int> tmp_ret = dfs(nxt, dist + 1);
            if (ret.second < tmp_ret.second) {
                ret = tmp_ret;
            }
        }
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 이동해야 하는 거리 중의 최대는 트리의 지름이다.
    * 이 중에서 최소를 고르면, 지름 안에 속하는 노드 중에서 하나를 선택한다.
    * 거리는 모두 1로 동일하므로, 지름을 2로 나눈 값을 반올림하면 된다.
    */

    cin >> n;
    for (int i = 0, n1, n2; i < n - 1; i++) {
        cin >> n1 >> n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    fill(visit + 1, visit + n + 1, false);
    visit[1] = true;
    int most_far = dfs(1, 0).first;
    
    fill(visit + 1, visit + n + 1, false);
    visit[most_far] = true;
    int max_dist = dfs(most_far, 0).second;

    cout << (max_dist % 2 == 0 ? max_dist / 2 : (max_dist + 1) / 2);

    return 0;
}