#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <functional>

using namespace std;

typedef pair<int, int> pint;
typedef pair<int, pint> edge;

int n, m, k;
vector<int> parent, set_size;
vector<bool> is_gen;
priority_queue<edge, vector<edge>, greater<edge>> pq;

int find_parent(int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

/*
* 일반적인 union_find에서 union을 약간 수정.
* 집합의 원소의 수까지 같이 업데이트
*/
void union_elem(int x, int y) {
    int f_x = find_parent(x);
    int f_y = find_parent(y);

    if (is_gen[f_x]) {
        parent[f_y] = f_x;
        set_size[f_x] += set_size[f_y];
        set_size[f_y] = 0;
    }
    else if(is_gen[f_y]){
        parent[f_x] = f_y;
        set_size[f_y] += set_size[f_x];
        set_size[f_x] = 0;
    }
    else {
        if (f_x > f_y) {
            swap(f_x, f_y);
        }
        parent[f_y] = f_x;
        set_size[f_x] += set_size[f_y];
        set_size[f_y] = 0;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    parent.resize(n + 1);
    set_size.resize(n + 1, 1);
    is_gen.resize(n + 1);
    for (int i = 0, gen; i < k; i++) {
        cin >> gen;
        is_gen[gen] = true;
    }
    iota(parent.begin(), parent.end(), 0);
    for (int i = 0, node1, node2, weight; i < m; i++) {
        cin >> node1 >> node2 >> weight;
        pq.push(edge(weight, pint(node1, node2)));
    }

    int conn_count = 0;
    int mst_sum = 0;
    /*
    * 크루스칼 알고리즘으로 mst를 만들면 되지만,
    * 일반 노드가 발전소에 연결되면 카운트 해줘야 한다.
    * 일반 노드의 수는 n - k이다.
    * 그리고, 이으려는 두 노드가 둘 다 발전소에 연결되어 있으면,
    * 연결할 필요가 없으므로 스킵.
    */
    while (!pq.empty() && conn_count < n - k) {
        int cur_weight = pq.top().first;
        pint nd = pq.top().second;
        pq.pop();

        int f1 = find_parent(nd.first);
        int f2 = find_parent(nd.second);
        if (f1 != f2 && !(is_gen[f1] && is_gen[f2])) {
            if (is_gen[f1] && !is_gen[f2]) {
                conn_count += set_size[f2];
            }
            else if (!is_gen[f1] && is_gen[f2]) {
                conn_count += set_size[f1];
            }

            union_elem(f1, f2);
            mst_sum += cur_weight;
        }
    }

    cout << mst_sum;

    return 0;
}