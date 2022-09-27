#include <iostream>
#include <vector>

using namespace std;

const int NOT_VISIT = -1;

int n, m, k, ans;
vector<int> graph[1001];
int match[1001];
bool visit[1001];

bool dfs(int cur) {
    visit[cur] = true;
    for(const int& work: graph[cur]) {
        if(match[work] == NOT_VISIT || (!visit[match[work]] && dfs(match[work]))) {
            match[work] = cur;
            return true;
        }
    }
    return false;
}

int main() {
    /**
     * 이분매칭으로 해결할 수 있다. 한 명의 일꾼에 하나의 작업을 먼저 매칭하고,
     * 다시 한 번 처음부터 매칭을 시도한다. 모든 일꾼에 대해 매칭을 시도했거나
     * 2개의 일이 매칭된 사람이 k명이 되면 이분매칭을 멈춘다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    for(int i = 1, num, wrk; i <= n; i++) {
        cin >> num;
        while(num--) {
            cin >> wrk;
            graph[i].push_back(wrk);
        }
    }

    fill(match + 1, match + m + 1, NOT_VISIT);
    for(int i = 1; i <= n; i++) {
        fill(visit + 1, visit + n + 1, false);
        if(dfs(i))
            ans++;
    }
    for(int i = 1, cnt = 0; i <= n && cnt < k; i++) {
        fill(visit + 1, visit + n + 1, false);
        if(dfs(i))
            ans++, cnt++;
    }

    cout << ans;

    return 0;
}