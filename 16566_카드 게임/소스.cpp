#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int n, m, k;
vector<int> card, parent;

int find_parent(int x) {
    return (parent[x] == x ? x : parent[x] = find_parent(parent[x]));
}

void union_elem(int x, int y) {
    int f_x = find_parent(x), f_y = find_parent(y);
    if (f_x >= f_y) {
        swap(f_x, f_y);
    }
    parent[f_x] = f_y;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    card.resize(m);
    parent.resize(m + 1);
    for (int& i : card) {
        cin >> i;
    }
    iota(parent.begin(), parent.end(), 0);
    sort(card.begin(), card.end());

    /*
    * �ѹ� ����� ī��� �ٽô� ����� �� ����.
    * ����, ����� ī���� ���� ī��� ���� �������� �����ش�.
    * ������ ��ǥ���� ���� ū ������ �����ϸ�, find_parent�� ������ ��
    * ���� ū �ε��� ���� ��ȯ�ȴ�. ����, ���� ���� �Է����� ���͵�
    * ���ǿ� �´� ����� �� �� �ְ� �ȴ�.
    */
    do {
        int low_bnd;
        cin >> low_bnd;

        auto ub = upper_bound(card.begin(), card.end(), low_bnd);
        int idx = find_parent(distance(card.begin(), ub));
        cout << card[idx] << '\n';

        union_elem(idx, idx + 1);
    } while (--k > 0);

    return 0;
}