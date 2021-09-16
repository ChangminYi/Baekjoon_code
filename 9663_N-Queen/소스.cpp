#include <iostream>
#include <vector>

using namespace std;

int n, cnt = 0;
vector<int> queen;

/*
* 만약 새로 놓은 퀸의 열이 이미 다른 퀸의 열과 겹치거나,
* 다른 퀸과 대각선상에 있다면 놓을 수 없음.
*/
bool can_place(int idx) {
    for (int i = 0; i < idx; i++) {
        if (queen[idx] == queen[i] || idx - i == abs(queen[idx] - queen[i])) {
            return false;
        }
    }
    return true;
}

/*
* queen[i]는 i행에 있는 퀸의 열 번호이다.
* 열마다 각각 하나씩 퀸을 놓아서 가능하다면 다음 열에도 놓는 것을 반복
*/
void find_n_queen(int idx) {
    if (idx == n) {
        cnt++;
    }
    else {
        for (int i = 0; i < n; i++) {
            queen[idx] = i;

            if (can_place(idx)) {
                find_n_queen(idx + 1);
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    queen.resize(n);

    find_n_queen(0);
    cout << cnt;

    return 0;
}