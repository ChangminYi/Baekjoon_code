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
    * 간선의 우선순위는 pair<int, int>를 따른다.
    * 그러므로 이중 for문을 돌려서 간선을 체크하게 되면,
    * 우선순위 순으로 간선을 탐색하는 것과 같다.
    * 입력을 받음과 동시에 mst를 만들고,
    * mst가 만들어지지 않았거나 추가로 간선을 더해 m개의 간선을 채우지 못한다면
    * -1을 출력한다. 아니라면 따로 저장해놨던 간선들을 차례로 더해
    * 정답을 완성하여 출력한다.
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