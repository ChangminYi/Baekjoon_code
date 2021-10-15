#include <iostream>

using namespace std;

/*
* 배열을 이용하면 더 빠르게 풀 수 있지만,
* 직관적으로 표현할 수 있는 리스트 형태로 구현.
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
    * 입력의 수를 정하지 않았기 때문에,
    * EOF가 나오기 전까지 계속 받는다.
    */
    while (cin >> val) {
        bintree = insert_tree(bintree, val);
    }

    post_order(bintree);

    return 0;
}