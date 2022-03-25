#include <iostream>
#include <queue>
#include <map>
#include <functional>

using namespace std;

int n, k, cnt;
int arg[500'000];
bool plugged[500'001];
queue<int> use_seq[500'001];
multimap<int, int, greater<>> in_use;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 플러그를 사용하는 방법은 총 세 가지의 경우의 수가 존재.
    * 첫 번째는 현재 번호가 이미 플러그에 있는 경우. 다음에 현재 번호가 나오는 순서만 업데이트한다.
    * 두 번째는 현재 번호가 플러그에 없고, 플러그가 모두 찬 경우.
    * 이 때는 다음에 나올 순서가 가장 뒤인 번호를 제거하고 자신을 삽입. 이 때 카운트가 올라간다.
    * 마지막은 현재 번호가 플러그에 없고, 플러그에 빈 칸이 있는 경우. 자기 번호를 삽입하면 된다.
    * 앞으로 사용하지 않을 번호의 경우, 우선순위가 겹칠 수 있어 multimap 사용.
    */

    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> arg[i];
        use_seq[arg[i]].push(i);
    }

    for (int i = 0, cur_seq; i < k; i++) {
        cur_seq = use_seq[arg[i]].front();
        use_seq[arg[i]].pop();

        if (plugged[arg[i]]) {
            in_use.erase(cur_seq);
            in_use.insert(make_pair(use_seq[arg[i]].empty() ? INT32_MAX : use_seq[arg[i]].front(), arg[i]));
        }
        else {
            if (in_use.size() == n) {
                cnt++;
                plugged[in_use.begin()->second] = false;
                in_use.erase(in_use.begin());
            }
            plugged[arg[i]] = true;
            in_use.insert(make_pair(use_seq[arg[i]].empty() ? INT32_MAX : use_seq[arg[i]].front(), arg[i]));
        }
    }

    cout << cnt;

    return 0;
}