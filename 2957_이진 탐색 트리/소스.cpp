#include <iostream>
#include <map>
#include <cmath>

using namespace std;

const int MIN = 0;
const int MAX = 300001;

int n, root;
map<int, int>::iterator ub, lb;
long long cnt = 0;
map<int, int> tree = {
    pair<int, int>(MIN, 0),
    pair<int, int>(MAX, 0)
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 문제의 의사 코드를 그대로 구현하면 시간초과. skewed 형태의 이진 트리가 나온다.
    * map을 이용하여 노드 번호와 그 노드의 깊이를 저장한다. 노드 번호는 유일하므로,
    * upper_bound를 사용하여 바로 다음 순서 노드를 구하고, 직전 순서 노드도 구한다.
    * 노드가 삽입되는 깊이는 직전, 다음 노드의 깊이의 최댓값 + 1이다.
    */
    cin >> n >> root;
    tree.insert(make_pair(root, 0));
    cout << 0 << '\n';
    for (int i = 1, cur_node, cur_depth; i < n; i++) {
        cin >> cur_node;
        ub = tree.upper_bound(cur_node);
        lb = ub; --lb;
        cur_depth = max(ub->second, lb->second) + 1;
        tree.insert(make_pair(cur_node, cur_depth));
        
        cnt += cur_depth;
        cout << cnt << '\n';
    }

    return 0;
}