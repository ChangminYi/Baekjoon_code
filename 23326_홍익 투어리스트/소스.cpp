#include <iostream>
#include <set>

using namespace std;

int n, q, cur = 1;
bool is_famous[500'001];
set<int> famous;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * lower_bound를 사용하면 자신보다 크거나 같은 번호 중 가장 가까운
    * 번호를 얻을 수 있다. 만약 없다면, 가장 앞의 번호가 가장 가까운 명소가 된다.
    * set을 이용하여 명소인 번호를 관리한다.
    */
    cin >> n >> q;
    for (int i = 1, tmp; i <= n; i++) {
        cin >> tmp;
        if (tmp) {
            is_famous[i] = true;
            famous.insert(i);
        }
        else {
            is_famous[i] = false;
        }
    }

    for (int inst, arg; q; q--) {
        cin >> inst;
        if (inst == 3) {
            if (famous.empty()) {
                cout << -1 << '\n';
            }
            else {
                auto lb = famous.lower_bound(cur);
                if (lb == famous.end()) {
                    cout << n - (cur - *famous.begin()) << '\n';
                }
                else {
                    cout << *lb - cur << '\n';
                }
            }
        }
        else {
            cin >> arg;
            if (inst == 1) {
                if (is_famous[arg]) {
                    is_famous[arg] = false;
                    famous.erase(arg);
                }
                else {
                    is_famous[arg] = true;
                    famous.insert(arg);
                }
            }
            else {
                cur = (cur - 1 + arg) % n + 1;
            }
        }
    }

    return 0;
}