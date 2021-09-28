#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <string>

using namespace std;

typedef pair<int, int> pint;

int n, m;
vector<int> edge_cnt, not_mst, parent;
vector<pint> remain_edge;
string tmp;

int find_parent(int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

void union_elem(int x, int y) {
    int f_x = find_parent(x);
    int f_y = find_parent(y);

    if (f_x > f_y) {
        swap(f_x, f_y);
    }

    parent[f_y] = f_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    edge_cnt.resize(n);
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);

    /*
    * ������ �켱������ pair<int, int>�� ������.
    * �׷��Ƿ� ���� for���� ������ ������ üũ�ϰ� �Ǹ�,
    * �켱���� ������ ������ Ž���ϴ� �Ͱ� ����.
    * �Է��� ������ ���ÿ� mst�� �����,
    * mst�� ��������� �ʾҰų� �߰��� ������ ���� m���� ������ ä���� ���Ѵٸ�
    * -1�� ����Ѵ�. �ƴ϶�� ���� �����س��� �������� ���ʷ� ����
    * ������ �ϼ��Ͽ� ����Ѵ�.
    */
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> tmp;

        for (int j = i + 1; j < n; j++) {
            if (tmp[j] == 'Y') {
                if (find_parent(i) != find_parent(j)) {
                    union_elem(i, j);
                    cnt++;
                    edge_cnt[i]++, edge_cnt[j]++;
                }
                else {
                    remain_edge.push_back(pint(i, j));
                }
            }
        }
    }

    if (cnt < n - 1 || cnt + remain_edge.size() < m) {
        cout << -1;
    }
    else {
        for (int i = 0; i < remain_edge.size() && cnt < m; i++) {
            int n1 = remain_edge[i].first;
            int n2 = remain_edge[i].second;

            cnt++;
            edge_cnt[n1]++, edge_cnt[n2]++;
        }

        for (const int& i : edge_cnt) {
            cout << i << ' ';
        }
    }

    return 0;
}