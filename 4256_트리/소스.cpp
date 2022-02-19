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
    * ���� ��ȸ�� ������ ��������, ���� ��ȸ���� ���� ��� ��ȣ�� �O�´�.
    * ����� �ε����� ��������, �� ���� ����Ʈ���� ������ ��������� Ž���ϰ�,
    * ���� ��ȸ�� ����� ����ؾ� �ϹǷ� ���� ��� ��ȣ�� ����Ѵ�.
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