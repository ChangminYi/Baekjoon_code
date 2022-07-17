#include <iostream>

using namespace std;

int n, cnt;
int arg[101];
bool visit[101], in_cycle[101];

bool dfs(const int cur, const int sp) {
    if(visit[cur])
        return false;
    else {
        visit[cur] = true;
        if(cur == sp || dfs(arg[cur], sp)) {
            cnt++;
            in_cycle[cur] = true;
        }
        return in_cycle[cur];
    }
}

int main() {
    /**
     * dfs를 통해 사이클을 판별하면 된다.
     * 시작 번호와 현재 노드 번호를 통해, 사이클 내부에 있는지를 판별.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> arg[i];

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++)
            visit[j] = in_cycle[j];
        dfs(arg[i], i);
    }

    cout << cnt << '\n';
    for(int i = 1; i <= n; i++) {
        if(in_cycle[i]) cout << i << '\n';
    }

    return 0;
}