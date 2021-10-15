#include <iostream>

using namespace std;

/*
* �迭�� �̿��ϸ� �� ������ Ǯ �� ������,
* ���������� ǥ���� �� �ִ� ����Ʈ ���·� ����.
*/
struct node {
    int val = 0;
    node* child_left = nullptr, * child_right = nullptr;
};

int val;
node* bintree;

node* insert_tree(node* cur, int new_val) {
    if (cur == nullptr) {
        cur = new node();
        cur->val = new_val;
    }
    else {
        if (new_val <= cur->val) {
            cur->child_left = insert_tree(cur->child_left, new_val);
        }
        else {
            cur->child_right = insert_tree(cur->child_right, new_val);
        }
    }

    return cur;
}

void post_order(node* cur) {
    if (cur->child_left != nullptr) {
        post_order(cur->child_left);
        free(cur->child_left);
    }
    if (cur->child_right != nullptr) {
        post_order(cur->child_right);
        free(cur->child_right);
    }

    cout << cur->val << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �Է��� ���� ������ �ʾұ� ������,
    * EOF�� ������ ������ ��� �޴´�.
    */
    while (cin >> val) {
        bintree = insert_tree(bintree, val);
    }

    post_order(bintree);

    return 0;
}