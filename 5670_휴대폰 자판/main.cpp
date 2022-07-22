#include <iostream>
#include <string>

using namespace std;

struct node {
    bool is_end;
    int child_cnt;
    node *child[26];
    node() {
        is_end = false;
        child_cnt = 0;
        fill(child, child + 26, nullptr);
    }
    ~node() {
        for(int i = 0; i < 26; i++) if(child[i]) delete child[i];
    }
};

int n;
string arg[100000];

void add_node(node *cur, const string& str) {
    for(int i = 0, idx; i < str.length(); i++) {
        idx = str[i] - 'a';
        if(cur->child[idx] == nullptr) {
            cur->child_cnt++;
            cur->child[idx] = new node;
        }
        cur = cur->child[idx];
    }
    cur->is_end = true;
}

int get_cnt(node *cur, const string& str) {
    int ret = 1;
    cur = cur->child[str[0] - 'a'];
    for(int i = 1; i < str.length(); i++) {
        if(cur->child_cnt != 1 || cur->is_end) ret++;
        cur = cur->child[str[i] - 'a'];
    }
    return ret;
}

int main() {
    /**
     * 트라이를 활용하여 해결할 수 있다. 입력받은 문자열을 미리 트라이에 저장한다.
     * 트라이의 노드에는 자식 노드의 수도 같이 세어 빠르게 판단이 가능하도록 한다.
     * 문자열을 탐색할 때, 자식이 여러 개이거나 자식이 한 개이고 해당 노드에서 끝나는 문자열이 있다면
     * 자판을 쳐야 하는 상황이다. 이런 상황의 수를 모두 더하여 문자열의 수로 나눠 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    (cout << fixed).precision(2);

    while(getline(cin, arg[0])) {
        n = stoi(arg[0]);
        for(int i = 0; i < n; i++) {
            cin >> arg[i];
        }
        
        node *head = new node;
        for(int i = 0; i < n; i++) {
            add_node(head, arg[i]);
        }

        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans += get_cnt(head, arg[i]);
        }

        cout << (long double)ans / n << '\n';

        delete head;
        cin.ignore();
    }

    return 0;
}