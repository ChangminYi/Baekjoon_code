#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct node {
    bool is_end;
    node *child[26];
    node() {
        is_end = false;
        fill(child, child + 26, nullptr);
    }
    ~node() {
        for(int i = 0; i < 26; i++) if(child[i]) delete child[i];
    }
};

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
};

const vector<dir> poss_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1),
    dir(1, 1), dir(-1, 1), dir(1, -1), dir(-1, -1)
};
const int score[9] = {
    0, 0, 0, 1, 1, 2, 3, 5, 11
};

int w, b;
node *head;
string trace = "";
char board[4][4];
bool visit[4][4];
set<string> str_set;

void add_trie(node *cur, const string& str) {
    for(int i = 0, nxt; i < str.length(); i++) {
        nxt = str[i] - 'A';
        if(cur->child[nxt] == nullptr) cur->child[nxt] = new node;
        cur = cur->child[nxt];
    }
    cur->is_end = true;
}

bool in_trie(node *cur, const string& str) {
    for(int i = 0, nxt; i < str.length(); i++) {
        nxt = str[i] - 'A';
        if(cur->child[nxt]) cur = cur->child[nxt];
        else return false;
    }
    return cur->is_end;
}

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < 4 && 0 <= d.col && d.col < 4;
}

void dfs(const dir cur) {
    trace.push_back(board[cur.row][cur.col]);
    str_set.insert(trace);

    if(trace.length() < 8) {
        for(const dir& pd: poss_dir) {
            dir nxt = cur + pd;
            if(in_range(nxt) && !visit[nxt.row][nxt.col]) {
                visit[nxt.row][nxt.col] = true;
                dfs(nxt);
                visit[nxt.row][nxt.col] = false;
            }
        }
    }

    trace.pop_back();
}

int main() {
    /**
     * 트라이를 사용하여 단어 사전을 구축한다.
     * 그 후, 그리드를 dfs로 탐색하여 만들 수 있는 모든 문자열을 저장한다.
     * 해당 문자열들을 트라이에서 검색하면서 점수의 합, 가장 긴 단어, 그리고 단어 수를 구한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    head = new node;

    cin >> w;
    for(string input; w; w--) {
        cin >> input;
        add_trie(head, input);
    }
    cin.ignore();

    cin >> b;
    do {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                cin >> board[i][j];
            }
        }
        cin.ignore();

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                visit[i][j] = true;
                dfs(dir(i, j));
                visit[i][j] = false;
            }
        }

        int total_score = 0, find_cnt = 0;
        string longest_str = "";
        for(const string& cur: str_set) {
            if(in_trie(head, cur)) {
                total_score += score[cur.length()];
                find_cnt++;
                if(cur.length() > longest_str.length()) longest_str = cur;
            }
        }

        cout << total_score << ' ' << longest_str << ' ' << find_cnt << '\n';

        str_set.clear();
    } while(--b);

    delete head;

    return 0;
}