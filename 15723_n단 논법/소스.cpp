#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int n, m;
vector<int> graph[26];
string tmp;
bool visit[26][26] = { false };
queue<int> que;

void bfs(const int start) {
    visit[start][start] = true;
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const int nxt : graph[cur]) {
            if (!visit[start][nxt]) {
                visit[start][nxt] = true;
                que.push(nxt);
            }
        }
    }
}

int ctoi(const char c) {
    return (int)(c - 'a');
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    (cin >> n).ignore();
    for (int i = 0; i < n; i++) {
        getline(cin, tmp);
        graph[ctoi(tmp.front())].push_back(ctoi(tmp.back()));
    }

    /*
    * 모든 노드에 대해서 방문할 수 있는 노드를 체크한다.
    * 그 후, 들어오는 입력에 따라서 결과만 출력하면 된다.
    */
    for (int i = 0; i < 26; i++) {
        bfs(i);
    }

    (cin >> m).ignore();
    for (int i = 0; i < m; i++) {
        getline(cin, tmp);
        cout << (visit[ctoi(tmp.front())][ctoi(tmp.back())] ? 'T' : 'F') << '\n';
    }

    return 0;
}