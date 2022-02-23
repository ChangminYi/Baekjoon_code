#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

struct edge {
    int node1, node2, weight;
};

int p, w, c, v;
int parent[1'001];
edge arg[50'000];

int find_parent(const int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

void union_set(const int x, const int y) {
    parent[find_parent(y)] = find_parent(x);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * union-find로도 풀 수 있고, 매개변수 탐색으로도 풀 수 있다.
    * union-find로 풀 경우, 모든 간선을 가중치 기준으로 내림차순 정렬하여
    * c와 v가 같은 집합이 될 때까지 두 노드를 합친다. 합쳐졌을 때의 간선의
    * 가중치가 가장 좁은 길의 너비이다.
    * 매개변수 탐색으로 풀 경우, 지나갈 수 있는 최대 너비를 기준으로
    * bfs를 실행하여 이분 탐색을 진행한다.
    * union-find가 매개변수 탐색보다 좀 더 빠르다.
    */

    cin >> p >> w >> c >> v;
    iota(parent, parent + p, 0);
    for (int i = 0; i < w; i++) {
        cin >> arg[i].node1 >> arg[i].node2 >> arg[i].weight;
    }

    sort(arg, arg + w,
        [](edge& lhs, edge& rhs) {
            return lhs.weight > rhs.weight;
        });

    for (int i = 0; i < w; i++) {
        union_set(arg[i].node1, arg[i].node2);
        if (find_parent(c) == find_parent(v)) {
            cout << arg[i].weight;
            break;
        }
    }

    return 0;
}