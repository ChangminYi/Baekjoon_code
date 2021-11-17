#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

const int NO_PARENT = -1;
typedef pair<int, int> pint;

int n, idx1, idx2;
string str;
stack<int> stk_bin, stk_idx;
vector<int> parent, depth, idx_to_num;
vector<pint> num_to_idx;

void init_par_dep() {
    parent[0] = NO_PARENT;
    depth[0] = 0;
    num_to_idx[0] = pint(0, n - 1);
    
    stk_bin.push(str[0]);
    stk_idx.push(0);
    for (int i = 1, cnt = 1; i < 2 * n; i++) {
        if (str[i] == '0') {
            parent[cnt] = stk_idx.top();
            depth[cnt] = depth[parent[cnt]] + 1;
            idx_to_num[i] = cnt;
            num_to_idx[cnt].first = i;

            stk_bin.push('0');
            stk_idx.push(cnt++);
        }
        else {
            idx_to_num[i] = stk_idx.top();
            num_to_idx[stk_idx.top()].second = i;

            stk_bin.pop();
            stk_idx.pop();
        }
    }
}

/*
* 최소 공통 조상 찾기. long(n)의 시간복잡도를 가지는
* 알고리즘도 있지만, 이 문제는 n이 충분히 작으므로
* 굳이 희소배열을 만들지 않고 탐색.
*/
int find_par(int x, int y) {
    int n1 = idx_to_num[x], n2 = idx_to_num[y];
    if (depth[n1] > depth[n2]) {
        swap(n1, n2);
    }

    while (depth[n1] < depth[n2]) {
        n2 = parent[n2];
    }
    if (n1 != n2) {
        while (n1 != n2) {
            n1 = parent[n1], n2 = parent[n2];
        }
    }

    return n2;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    parent.resize(n);
    depth.resize(n);
    idx_to_num.resize(2 * n);
    num_to_idx.resize(n);

    cin >> str;
    /*
    * 입력 문자열을 기준으로 트리를 구성.
    * '0'이 나오면 그 전의 숫자의 자식 노드이다. 직전에 나왔던 부모 노드와 연결해준다.
    * '1'이 나오면 terminal 노드에 온 것이므로, pop.
    */
    init_par_dep();

    cin >> idx1 >> idx2;
    int par = find_par(idx1 - 1, idx2 - 1);
    cout << num_to_idx[par].first + 1 << ' ' << num_to_idx[par].second + 1;

    return 0;
}