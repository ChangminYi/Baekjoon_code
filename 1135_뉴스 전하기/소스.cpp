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
    * Ʈ���� �� ��忡��, �ڽĵ��� ������ �� �ִ� ���� ���� �ð��� ����.
    * �� �ð����� ������������ ������ ��, ���������� �����ϸ鼭 ����
    * ���� �ɸ��� �ð��� ã�Ƽ� ��ȯ�ϸ� ��.
    */
    cout << dfs(0) - 1;

    return 0;
}