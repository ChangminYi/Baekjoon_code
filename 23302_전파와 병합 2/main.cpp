#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0): row(_r), col(_c) {}
};

int r, c;
string tmp;
vector<dir> graph[1000][703];
int in_degree[1000][703];
queue<dir> que;

dir conv_str(const string s) {
    dir ret;
    for(int i = 0; i < s.length(); i++) {
        if(isalpha(s[i])) {
            ret.col *= 26;
            ret.col += s[i] - 'A' + 1;
        }
        else {
            ret.row = stoi(s.substr(i));
            break;
        }
    }
    return ret;
}

vector<dir> get_dir(const string s) {
    vector<dir> ret;
    if(s[0] != '.') {
        int idx = -1;
        for(int i = 0; i < s.length() && idx == -1; i++) {
            if(s[i] == '+') idx = i;
        }

        if(idx == -1) ret.push_back(conv_str(s));
        else {
            ret.push_back(conv_str(s.substr(0, idx + 1)));
            ret.push_back(conv_str(s.substr(idx + 1)));
        }
    }
    return ret;
}

int main() {
    /**
     * 그래프의 사이클 존재 유무 판별 문제.
     * 문자열로 주어지는 좌표를 파싱하여 행렬의 인덱스로 변환한다.
     * 위상 정렬을 통해 사이클이 존재하는지 판단하면 해결할 수 있다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> r >> c;
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <=c; j++) {
            cin >> tmp;
            vector<dir> from = get_dir(tmp);
            for(const dir& d: from) {
                graph[d.row][d.col].push_back(dir(i, j));
            }
            in_degree[i][j] += from.size();
        }
    }
    
    for(int i = 1; i <= r; i++) {
        for(int j = 1; j <= c; j++) {
            if(in_degree[i][j] == 0 && !graph[i][j].empty()) que.push(dir(i, j));
        }
    }
    while(!que.empty()) {
        dir cur = que.front();
        que.pop();

        for(const dir& nxt: graph[cur.row][cur.col]) {
            if(--in_degree[nxt.row][nxt.col] == 0) que.push(nxt);
        }
    }

    bool flag = true;
    for(int i = 1; i <= r && flag; i++) {
        for(int j = 1; j <= c && flag; j++) {
            if(in_degree[i][j] != 0) flag = false;
        }
    }

    cout << (flag ? "no" : "yes");

    return 0;
}