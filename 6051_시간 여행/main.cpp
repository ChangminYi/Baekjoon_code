#include <iostream>

using namespace std;

char inst;
int n, add_list[800001], parent[800001];

int main() {
    /**
     * 과거로 시간여행한 뒤 다시 미래로 갈 수 없다.
     * 데이터 중 현재와 가장 가까운 시간에 추가된 데이터의 위치와
     * 해당 시간의 직전 추가 위치만을 기억하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    add_list[0] = -1, parent[0] = 0;

    cin >> n;
    for(int i = 1, cur_head = 0, tmp; i <= n; i++) {
        cin >> inst;
        parent[i] = cur_head;
        if(inst == 'a') {
            cin >> add_list[i];
            cur_head = i;
        }
        else if(inst == 't') {
            cin >> tmp;
            cur_head = parent[tmp];
        }
        else {
            cur_head = parent[cur_head];
        }

        cout << add_list[cur_head] << '\n';
    }

    return 0;
}
