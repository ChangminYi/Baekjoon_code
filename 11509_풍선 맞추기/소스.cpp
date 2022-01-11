#include <iostream>
#include <map>

using namespace std;

int n, cnt = 0;
map<int, int> arg;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 높이 h에서 풍선을 맞추면, h-1로 높이가 내려가고 계속 진행한다.
    * 따라서, 현재 위치 이전에 h+1의 높이의 풍선이 있다면, 그 풍선을 맞춘
    * 화살은 현재 위치를 맞추게 될 것이다. 따라서 입력을 받으면서 풍선의 수를
    * 저장하고, 화살의 수를 계속 업데이트하면 된다.
    */
    cin >> n;
    for (int i = 0, cur; i < n; i++) {
        cin >> cur;

        if (arg.find(cur) == arg.end()) {
            arg.insert(make_pair(cur, 1));
        }
        else {
            arg[cur]++;
        }

        if (arg.find(cur + 1) == arg.end()) {
            cnt++;
        }
        else {
            if (--arg[cur + 1] == 0) {
                arg.erase(cur + 1);
            }
        }
    }

    cout << cnt;

    return 0;
}