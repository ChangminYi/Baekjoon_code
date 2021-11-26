#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct edge {
    int n1 = 0, n2 = 0, weight = 0;
    edge(int _n1, int _n2, int _w) : n1(_n1), n2(_n2), weight(_w) {}
    bool operator> (const edge& other) const {
        return this->weight > other.weight;
    }
};

int n, m;
vector<int> parent;
priority_queue<edge, vector<edge>, greater<edge>> pq;

int find_parent(const int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

void union_elem(const int x, const int y) {
    int f_x = find_parent(x), f_y = find_parent(y);
    if (f_x > f_y) {
        swap(f_x, f_y);
    }
    parent[f_y] = f_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    parent.resize(n + 1);
    iota(parent.begin(), parent.end(), 0);

    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        pq.push(edge(n1, n2, w));
    }

    /*
    * �ּ� ���� Ʈ�� �˰���.
    * ������ ������ ��� �����Ͽ� ����ġ �������� �������� �����ϰ�,
    * �� ��尡 �ٸ� �����̶�� ������ �� ����ġ�� ����.
    * �̾��� ������ n-1���� �Ǹ� Ʈ���� �ϼ��ǹǷ�, ����ġ ���� ���.
    */
    int total_sum = 0;
    for (int i = 0; i < n - 1;) {
        int f1 = find_parent(pq.top().n1);
        int f2 = find_parent(pq.top().n2);
        int weight = pq.top().weight;
        pq.pop();

        if (f1 != f2) {
            union_elem(f1, f2);
            total_sum += weight;
            i++;
        }
    }

    cout << total_sum;

    return 0;
}