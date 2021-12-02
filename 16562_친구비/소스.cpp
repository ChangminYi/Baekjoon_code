#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, m ,k;
vector<int> parent, min_cost;

int find_par(const int x) {
    return parent[x] == x ? x : parent[x] = find_par(parent[x]);
}

void union_elem(const int x, const int y) {
    int p_x = find_par(x);
    int p_y = find_par(y);
    if (p_x > p_y) {
        swap(p_x, p_y);
    }

    parent[p_y] = p_x;
    min_cost[p_x] = min(min_cost[p_x], min_cost[p_y]);
    min_cost[p_y] = 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    parent.resize(n + 1);
    min_cost.resize(n + 1);

    /*
    * union-find를 사용하여, 이미 친구인 사람들을 한 집합으로 묶는다.
    * 그 과정에서, 집합과 최소비용으로 친구가 되기 위한 비용을 저장한다.
    * 그 후, 집합의 대표값에 대해서 비용 계산, 조건 확인하여 출력.
    */
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        cin >> min_cost[i];
    }
    for (int i = 0, x, y; i < m; i++) {
        cin >> x >> y;
        union_elem(x, y);
    }

    int t_cost = 0;
    for (int i = 1; i <= n; i++) {
        if (min_cost[i]) {
            t_cost += min_cost[i];
        }
    }

    if (t_cost <= k) {
        cout << t_cost;
    }
    else {
        cout << "Oh no";
    }

    return 0;
}