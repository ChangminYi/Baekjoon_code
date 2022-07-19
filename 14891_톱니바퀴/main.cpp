#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int k;
string cogwheel[5];

bool can_rotate(const int lhs, const int rhs) {
    return cogwheel[lhs][2] != cogwheel[rhs][6];
}

void rotate_cogwheel(const int idx, const int dir) {
    char tmp;
    if(dir == 1) {
        tmp = cogwheel[idx][7];
        for(int i = 7; i > 0; i--) {
            cogwheel[idx][i] = cogwheel[idx][i - 1];
        }
        cogwheel[idx][0] = tmp;
    }
    else {
        tmp = cogwheel[idx][0];
        for(int i = 0; i < 7; i++) {
            cogwheel[idx][i] = cogwheel[idx][i + 1];
        }
        cogwheel[idx][7] = tmp;
    }
}

int main() {
    /**
     * 톱니바퀴가 돌아갈 때 같이 돌 수 있는 것은 좌우의 극이 서로 다를 때.
     * 따라서 돌아갈 수 있는 톱니바퀴들을 모두 구한 다음, 원래 돌린 톱니바퀴와의
     * 인덱스 차이가 홀수이면 반대방향, 짝수이면 같은 방향으로 돌린다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    for(int i = 1; i <= 4; i++)
        cin >> cogwheel[i];

    cin >> k;
    for(int idx, dir, lo, hi; k; k--) {
        cin >> idx >> dir;
        lo = idx, hi = idx;
        while(lo > 1 && can_rotate(lo - 1, lo)) lo--;
        while(hi < 4 && can_rotate(hi, hi + 1)) hi++;

        for(int i = lo; i <= hi; i++)
            rotate_cogwheel(i, (abs(idx - i) % 2 ? -dir : dir));
    }

    int ans = 0;
    for(int i = 1; i <= 4; i++)
        ans |= (cogwheel[i][0] == '1' ? (1 << (i - 1)) : 0);

    cout << ans;

    return 0;
}