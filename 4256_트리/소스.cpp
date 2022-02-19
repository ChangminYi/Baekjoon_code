#include <iostream>

using namespace std;

int t, n;
int inorder[1'001], preorder[1'001];

void do_post(int idx, int lo, int hi) {
    for (int i = lo; i < hi; i++) {
        if (preorder[idx] == inorder[i]) {
            do_post(idx + 1, lo, i);
            do_post(idx - lo + i + 1, i + 1, hi);
            cout << inorder[i] << ' ';
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 전위 순회의 순서를 기준으로, 중위 순회에서 같은 노드 번호를 찿는다.
    * 노드의 인덱스를 기준으로, 두 개의 서브트리로 나누어 재귀적으로 탐색하고,
    * 후위 순회의 결과를 출력해야 하므로 현재 노드 번호를 출력한다.
    */

    cin >> t;
    do {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> preorder[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> inorder[i];
        }

        do_post(0, 0, n);
        cout << '\n';
    } while (--t);

    return 0;
}