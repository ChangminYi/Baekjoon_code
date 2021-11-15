#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, q;
vector<int> ub, cnt;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    ub.resize(n + 1, 1);
    cnt.resize(n + 1, 0);

    /*
    * 임의의 두 도시 사이는 언제나 유일한 경로이기 때문에, 트리 구조.
    * 다음 나라의 시작 번호를 저장하여, 입력되는 섬의 국가를 구분.
    * 초기 상태의 국가의 섬 갯수는 전체 섬-다리의 수와 같다.
    */
    for (int i = 1, sum = 1, total_land, bridge; i <= n; i++) {
        cin >> total_land >> bridge;

        sum += total_land;
        ub[i] = sum;
        cnt[i] = total_land - bridge;
        for (int j = 0, dummy1, dummy2; j < bridge; j++) {
            cin >> dummy1 >> dummy2;
        }
    }

    /*
    * 다른 나라의 섬을 뺏는 경우는 없음. 따라서, 자신의 섬의 수만 조절 가능.
    * 입력으로 들어오는 두 섬은 언제나 같은 국가에 소속되어 있음.
    * 만약 다리가 끊어지면 섬의 수가 늘어나고, 연결되면 줄어듦.
    * 이분탐색으로 입력되는 섬의 국가를 검색할 수 있음.
    */
    cin >> q;
    do {
        int inst, idx;
        cin >> inst;

        if (inst == 1) {
            cin >> idx;
            cout << cnt[idx] << '\n';
        }
        else {
            int arg1, arg2;
            cin >> arg1 >> arg2;

            idx = distance(ub.begin(), upper_bound(ub.begin(), ub.end(), arg1));
            inst == 2 ? cnt[idx]++ : cnt[idx]--;
        }
    } while (--q);

    return 0;
}