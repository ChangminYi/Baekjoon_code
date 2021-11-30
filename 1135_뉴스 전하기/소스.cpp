#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> tree;

int dfs(const int cur) {
    int ret = 0;
    vector<int> child_time;
    int weight = (int)tree[cur].size() - 1;

    for (const int& chd : tree[cur]) {
        child_time.push_back(dfs(chd));
    }

    sort(child_time.begin(), child_time.end());
    for (const int& t : child_time) {
        ret = max(ret, t + weight--);
    }

    return ret + 1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    tree.resize(n);
    
    for (int i = 0, par; i < n; i++) {
        cin >> par;
        if (par >= 0) {
            tree[par].push_back(i);
        }
    }

    /*
    * 트리의 각 노드에서, 자식들이 전파할 수 있는 가장 빠른 시간을 얻음.
    * 그 시간들을 오름차순으로 정렬한 후, 순차적으로 전파하면서 가장
    * 오래 걸리는 시간을 찾아서 반환하면 됨.
    */
    cout << dfs(0) - 1;

    return 0;
}