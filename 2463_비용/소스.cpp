#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;
typedef pair<int, pint> edge;
typedef long long lli;

const lli MOD = 1000000000;

int n, m;
lli sum = 0, res = 0;
vector<int> parent, set_size;
vector<edge> arg;

int find_parent(const int x) {
    return (parent[x] == x ? x : (parent[x] = find_parent(parent[x])));
}

void union_elem(const int x, const int y) {
    int f_x = find_parent(x), f_y = find_parent(y);
    if (f_x > f_y) {
        swap(f_x, f_y);
    }

    parent[f_y] = f_x;
    set_size[f_x] += set_size[f_y];
    set_size[f_y] = 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    parent.resize(n + 1);
    set_size.resize(n + 1, 1);
    arg.resize(m);

    iota(parent.begin(), parent.end(), 0);
    for (int i = 0; i < m; i++) {
        cin >> arg[i].second.first >> arg[i].second.second >> arg[i].first;
        
        // u < v�� ������ֱ� (�ʼ��� �ƴ�)
        if (arg[i].second.first > arg[i].second.second) {
            swap(arg[i].second.first, arg[i].second.second);
        }
        sum += arg[i].first;
    }

    /*
    * ������ ����ġ �������� �������� ����.
    * ������ ��� �߰��ϴٰ�, Ư�� ������ �߰����� �� �������� ������
    * �������� ������ ������ζ�� Cost(u, v)�� ���ϴ� ����.
    * ����, �������� ������ �����ִ�, ���� �߰����� ���� ����(Cost�� ���ϱ� ���� �����Ǵ� ����)��
    * �̵��� �����ϴ� ������ ���� ����Ͽ� �� ���� ���� �� ����.
    */
    sort(arg.rbegin(), arg.rend());

    for (int i = 0, p1, p2, weight; i < m; i++) {
        p1 = find_parent(arg[i].second.first);
        p2 = find_parent(arg[i].second.second);
        weight = arg[i].first;

        if (p1 != p2) {
            // �ڷ��� ���� ����.
            res += ((((lli)set_size[p1] * set_size[p2]) % MOD) * sum) % MOD;
            res %= MOD;

            union_elem(p1, p2);
        }

        sum -= weight;
    }

    cout << res;

    return 0;
}