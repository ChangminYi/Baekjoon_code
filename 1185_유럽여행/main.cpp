#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

struct edge {
    int node[2], weight;
};

int n, p, ans = INT32_MAX;
int cost[10001], par[10001];
edge arg[100000];

int find_par(const int x) {
    return (x == par[x] ? x : par[x] = find_par(par[x]));
}

void union_set(const int x, const int y) {
    par[find_par(x)] = find_par(y);
}

int main() {
    /**
     * n-1개의 간선만을 남기기 때문에, 모든 나라를 순회하는 mst 문제이다.
     * 따라서, mst를 이루는 간선은 반드시 왕복하여 지나간다.
     * 간선의 가중치를 2 * L과 S와 E의 비용의 합으로 정한다.
     * 그 후, mst를 구축하여 비용을 구하고, 처음 시작하는 나라의 비용을 더한다.
     * 최솟값을 구해야 하므로 나라의 비용 중 최솟값을 더하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> p;
    for(int i = 1; i <= n; i++) {
        cin >> cost[i];
        ans = min(ans, cost[i]);
    }
    for(int i = 0, l; i < p; i++) {
        cin >> arg[i].node[0] >> arg[i].node[1] >> l;
        arg[i].weight = 2 * l + cost[arg[i].node[0]] + cost[arg[i].node[1]];
    }

    sort(arg, arg + p, [](edge& lhs, edge& rhs) {
        return lhs.weight < rhs.weight;
    });

    iota(par, par + n + 1, 0);
    for(int i = 0, cnt = 0; i < p && cnt < n - 1; i++) {
        if(find_par(arg[i].node[0]) == find_par(arg[i].node[1]))
            continue;
        cnt++;
        union_set(arg[i].node[0], arg[i].node[1]);
        ans += arg[i].weight;
    }

    cout << ans;

    return 0;
}