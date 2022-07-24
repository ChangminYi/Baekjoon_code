#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct node {
    node *child[26];
    node() {
        fill(child, child + 26, nullptr);
    }
    ~node() {
        for(int i = 0; i < 26; i++) if(child[i]) delete child[i];
    }
};

int n;
node *head;
unordered_map<string, int> name_cnt;

int add_trie(node *cur, const string str) {
    int ret = 0;
    for(int i = 0, idx; i < str.length(); i++) {
        idx = str[i] - 'a';
        if(cur->child[idx] == nullptr) {
            if(ret == 0) ret = i + 1;
            cur->child[idx] = new node;
        }
        cur = cur->child[idx];
    }
    return (ret ? ret : str.length());
}

int main() {
    /**
     * 트라이와 set을 이용하여 닉네임을 관리할 수 있다.
     * 아직 등록하지 않은 닉네임이 들어오면, set에 닉네임을 추가하고
     * 트라이에서 첫 번째 분기점까지를 별칭으로 사용한다.
     * 만약 트라이에서 분기점을 발견하지 못했다면 전체 문자열을 별칭으로 사용한다.
     * 등록된 닉네임이 들어오면, 닉네임 카운트를 증가시킨다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    head = new node;

    cin >> n;
    for(string input; n; n--) {
        cin >> input;
        if(name_cnt.find(input) != name_cnt.end()) {
            cout << input << ++name_cnt[input] << '\n';
        }
        else {
            name_cnt.insert(make_pair(input, 1));
            cout << input.substr(0, add_trie(head, input)) << '\n';
        }
    }

    delete head;

    return 0;
}