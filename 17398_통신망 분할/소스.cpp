#include <iostream>
#include <stack>

using namespace std;

int n, m, q;
int edge[100001][2];
bool init_avl[100001];
int par[100001];
long long set_size[100001];
stack<int> cut_idx;

int find_par(const int x) {
    return par[x] == x ? x : par[x] = find_par(par[x]);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 그래프를 만들 때, 컷할 간선들은 연결하지 않고 저장만 한다.
    * 나머지 간선들을 모두 연결한 상태에서, 간선 삭제 순서의 반대로
    * 간선을 잇기 시작한다. 이 때 부분 그래프의 크기를 업데이트하면서
    * 비용의 총합을 계산하면 된다.
    */
    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
        par[i] = i, set_size[i] = 1;
    }
    for (int i = 1; i <= m; i++) {
        init_avl[i] = true;
        cin >> edge[i][0] >> edge[i][1];
    }
    for (int i = 0, idx; i < q; i++) {
        cin >> idx;
        init_avl[idx] = false;
        cut_idx.push(idx);
    }

    for (int i = 1, fx, fy; i <= m; i++) {
        if (init_avl[i]) {
            fx = find_par(edge[i][0]), fy = find_par(edge[i][1]);
            if (fx != fy) {
                par[fy] = fx;
                set_size[fx] += set_size[fy];
                set_size[fy] = 0;
            }
        }
    }

    long long sum = 0;
    while (!cut_idx.empty()) {
        int idx = cut_idx.top();
        cut_idx.pop();

        int fx = find_par(edge[idx][0]), fy = find_par(edge[idx][1]);
        if (fx != fy) {
            sum += set_size[fx] * set_size[fy];
            par[fy] = fx;
            set_size[fx] += set_size[fy];
            set_size[fy] = 0;
        }
    }

    cout << sum;

    return 0;
}