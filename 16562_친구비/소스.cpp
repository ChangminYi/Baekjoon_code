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
    * union-find�� ����Ͽ�, �̹� ģ���� ������� �� �������� ���´�.
    * �� ��������, ���հ� �ּҺ������ ģ���� �Ǳ� ���� ����� �����Ѵ�.
    * �� ��, ������ ��ǥ���� ���ؼ� ��� ���, ���� Ȯ���Ͽ� ���.
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