#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

typedef long long lli;

const int MAX = 123456;

int n;
vector<int> sheep, wolf;
vector<lli> dp;
vector<vector<int>> graph;
bitset<MAX + 1> visit;

void dfs(const int cur) {
    dp[cur] = sheep[cur];

    for (const int& nxt : graph[cur]) {
        if (!visit[nxt]) {
            visit[nxt] = true;
            dfs(nxt);

            dp[cur] += dp[nxt];
        }
    }

    dp[cur] = max(dp[cur] - wolf[cur], 0LL);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    visit.reset();
    graph.resize(n + 1);
    sheep.resize(n + 1, 0);
    wolf.resize(n + 1, 0);
    dp.resize(n + 1, 0);

    for (int i = 2; i <= n; i++) {
        char type;
        int num, adj;
        cin >> type >> num >> adj;

        type == 'S' ? sheep[i] = num : wolf[i] = num;
        graph[i].push_back(adj);
        graph[adj].push_back(i);
    }

    /*
    * dfs + Ʈ�������� dp ����.
    * ��Ʈ���� ���� �켱 Ž���� �����ϸ鼭 dp �迭�� �ʱ�ȭ�ϰ�,
    * �ڽ� ��忡�� �� �� �ִ� ���� ���� ��� ���� ����,
    * ���� ����� ���� ����ŭ �� ���� 0 �߿� ū ����
    * ���� ��忡 �� �� �ִ� ��� ���� ��.
    */
    visit[1] = true;
    dfs(1);

    cout << dp[1];

    return 0;
}