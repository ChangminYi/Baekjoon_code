#include <iostream>
#include <numeric>

using namespace std;

struct edge {
    int node1, node2;
};

int n, m, k;
edge arg[10'000];
int parent[1'001];
bool usable[10'000];

int find_parent(const int x) {
    if (parent[x] == x) return x;
    else return parent[x] = find_parent(parent[x]);
}

void union_set(const int x, const int y) {
    parent[find_parent(y)] = find_parent(x);
}

int make_mst() {
    int cnt = 0, mst_weight = 0;
    bool erased = false;
    iota(parent, parent + n + 1, 0);

    for (int i = 0; i < m && cnt < n - 1; i++) {
        if (usable[i] && find_parent(arg[i].node1) != find_parent(arg[i].node2)) {
            cnt++;
            mst_weight += i + 1;
            union_set(arg[i].node1, arg[i].node2);
            if (!erased) {
                erased = true;
                usable[i] = false;
            }
        }
    }

    return (cnt == n - 1 ? mst_weight : 0);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 간선의 가중치는 간선의 인덱스 + 1로 설정할 수 있다.
    * 오름차순으로 미리 정렬되어 들어오기 때문에 따로 정렬하지 않는다.
    * 문제에서 주어진 조건에 맞게 mst를 만들면서 간선을 하나씩 지우고,
    * 처음으로 만들 수 없는 순간부터 모두 0을 출력하고 종료한다.
    */

    cin >> n >> m >> k;
    fill(usable, usable + m, true);
    for (int i = 0; i < m; i++) {
        cin >> arg[i].node1 >> arg[i].node2;
    }

    for (int i = 0, res; i < k; i++) {
        if (res = make_mst()) {
            cout << res << ' ';
        }
        else {
            for (int j = i; j < k; j++) {
                cout << "0 ";
            }
            break;
        }
    }

    return 0;
}