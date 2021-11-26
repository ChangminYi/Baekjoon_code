#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MOD = 1000;

int testcase, n;
vector<int> parent, dist;

int find_parent(const int x) {
    if (parent[x] == x) {
        return x;
    }
    else {
        int center = find_parent(parent[x]);
        dist[x] += dist[parent[x]];
        return parent[x] = center;
    }
}

void union_elem(const int from, const int to) {
    dist[from] = abs(from - to) % MOD;
    parent[from] = to;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    (cin >> testcase).ignore();
    do {
        (cin >> n).ignore();
        
        parent = vector<int>(n + 1);
        dist = vector<int>(n + 1, 0);
        iota(parent.begin(), parent.end(), 0);

        /*
        * �и� ����. Union-find ���.
        * ������ ���� ����Ǹ�, union�� �����ϸ� �� ��� ���Ḹ �ϰ� ���� �Ÿ� �ʱ�ȭ.
        * find������ ���ͱ����� �Ÿ��� ������Ʈ. ��� ������ find �����Ͽ� �Ÿ� �ֽ�ȭ.
        * �Է� ���� ����. ignore() ����Ͽ� ���� ����.
        */
        while (true) {
            char inst;
            (cin >> inst).ignore();

            if (inst == 'E') {
                int arg;
                (cin >> arg).ignore();
                find_parent(arg);
                cout << dist[arg] << '\n';
            }
            else if (inst == 'I') {
                int arg1, arg2;
                (cin >> arg1 >> arg2).ignore();
                union_elem(arg1, arg2);
            }
            else {
                break;
            }
        }
    } while (--testcase);

    return 0;
}