#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

struct node {
    bool is_end;
    node *child[26];

    node() {
        is_end = false;
        fill(child, child + 26, nullptr);
    }
    ~node() {
        for(int i = 0; i < 26; i++) {
            if(child[i]) delete child[i];
        }
    }
};

int c, n, q;
string input;
node *color_head = new node;
unordered_set<string> name_set;

void add_node(node *cur, const string& str) {
    for(int i = 0, nxt_idx; i < str.length(); i++) {
        nxt_idx = str[i] - 'a';
        if(cur->child[nxt_idx] == nullptr) cur->child[nxt_idx] = new node();
        cur = cur->child[nxt_idx];
    }
    cur->is_end = true;
}

bool get_query(node *cur, const string& str) {
    for(int i = 0, nxt_idx; i < str.length(); i++) {
        if(cur == nullptr) return false;
        else if(cur->is_end && name_set.find(str.substr(i)) != name_set.end()) return true;
        cur = cur->child[str[i] - 'a'];
    }
    return false;
}

int main() {
    /**
     * 트라이를 사용하여 문자열 탐색을 빠르게 할 수 있다.
     * 다만, 트라이는 메모리 낭비가 심하므로 색상만 트라이에 저장하고 닉네임은 unordered_set으로 관리한다.
     * 색상 트라이에 대해서 탐색을 하면서, 색상이 끝나면 해당 지점에서 남은 문자열로 닉네임을 검색.
     * 결과가 존재한다면 해당 팀 이름은 가능한 팀 이름이고, 없다면 다시 트라이 탐색을 진행한다.
     * 트라이를 끝까지 탐색했을 때까지 닉네임을 발견하지 못했다면 불가능한 팀 이름이다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> c >> n;
    for(int i = 0; i < c; i++) {
        cin >> input;
        add_node(color_head, input);
    }
    for(int i = 0; i < n; i++) {
        cin >> input;
        name_set.insert(input);
    }
    
    cin >> q;
    do {
        cin >> input;
        cout << (get_query(color_head, input) ? "Yes\n" : "No\n");
    } while(--q);

    delete color_head;

    return 0;
}