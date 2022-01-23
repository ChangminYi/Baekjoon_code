#include <iostream>

using namespace std;

struct node {
    int left_child, right_child;
};

const int NO_CHILD = -1;

int n;
long long cnt = -1;
node tree[100001];
bool returnable[100001];

void dfs(const int cur) {
    cnt++;
    if (tree[cur].left_child != NO_CHILD) {
        dfs(tree[cur].left_child);
        cnt++;
    }
    if (tree[cur].right_child != NO_CHILD) {
        dfs(tree[cur].right_child);
        if (returnable[cur]) {
            cnt++;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 중위 순회를 기반으로 진행하지만, 각 노드의 자식들을 순회하고 돌아올 때도 카운트.
    * 트리의 가장 오른쪽 간선들은 돌아오지 않으므로, 세지 않음.
    */
    cin >> n;
    fill(returnable + 1, returnable + n + 1, true);
    for (int i = 1, par; i <= n; i++) {
        cin >> par;
        cin >> tree[par].left_child >> tree[par].right_child;
    }
    for (int cur = 1; cur != NO_CHILD; cur = tree[cur].right_child) {
        returnable[cur] = false;
    }

    dfs(1);

    cout << cnt;
    
    return 0;
}