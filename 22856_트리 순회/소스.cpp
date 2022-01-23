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
    * ���� ��ȸ�� ������� ����������, �� ����� �ڽĵ��� ��ȸ�ϰ� ���ƿ� ���� ī��Ʈ.
    * Ʈ���� ���� ������ �������� ���ƿ��� �����Ƿ�, ���� ����.
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