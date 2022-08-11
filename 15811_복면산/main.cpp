#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string arg[3];
vector<char> ch_set;
int val[26];
bool used[10];

unsigned long long get_dec(const string& str) {
    unsigned long long ret = 0;
    for(char c: str) {
        ret = 10 * ret + val[c - 'A'];
    }
    return ret;
}

bool dfs(int depth) {
    if(depth == ch_set.size())
        return get_dec(arg[0]) + get_dec(arg[1]) == get_dec(arg[2]);
    else {
        for(int i = 0; i <= 9; i++) {
            if(used[i]) continue;
            used[i] = true;
            val[ch_set[depth] - 'A'] = i;
            if(dfs(depth + 1)) return true;
            used[i] = false;
        }
        return false;
    }
}

int main() {
    /**
     * 알파벳의 종류가 10개를 초과하면 만들 수 있는 답은 없다.
     * 최대 10개의 알파벳의 경우만을 보면 되므로, 브루트포스 방식으로 탐색한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    for(int i = 0; i < 3; i++) {
        cin >> arg[i];
        for(char c: arg[i]) {
            ch_set.push_back(c);
        }
    }

    sort(ch_set.begin(), ch_set.end());
    ch_set.erase(unique(ch_set.begin(), ch_set.end()), ch_set.end());

    if(ch_set.size() > 10) 
        cout << "NO";
    else
        cout << (dfs(0) ? "YES" : "NO");

    return 0;
}
