#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
vector<int> graph[2'001], bombed;
bool origin_destroy[2'001], rep_destroy[2'001];

bool is_same_map() {
    for (int i = 1; i <= n; i++) {
        if (origin_destroy[i] != rep_destroy[i]) return false;
    }
    return true;
}

bool adj_all_destroyed(const int cur) {
    for (const int& adj : graph[cur]) {
        if (!origin_destroy[adj]) return false;
    }
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 만약 자신도 폭격되었고, 인접 도시가 모두 폭격되었다면 도시 번호를 저장한다.
    * 이를 통해서 폭격 상황을 새로 만들고, 입력으로 받은 상황과 같은지 비교한다.
    * 이 방법을 통해서 구한 답은 도시가 가장 많이 폭격당한 경우가 된다.
    */

    cin >> n >> m;
    for (int n1, n2; m; m--) {
        cin >> n1 >> n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }
    cin >> k;
    for (int i; k; k--) {
        cin >> i;
        origin_destroy[i] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (origin_destroy[i] && adj_all_destroyed(i)) {
            bombed.push_back(i);
            rep_destroy[i] = true;
            for (const int& adj : graph[i]) {
                rep_destroy[adj] = true;
            }
        }
    }

    if (is_same_map()) {
        cout << bombed.size() << '\n';
        for (const int& i : bombed) {
            cout << i << ' ';
        }
    }
    else {
        cout << -1;
    }

    return 0;
}