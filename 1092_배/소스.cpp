#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> crane, box;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    crane.resize(n);
    for (int& i : crane) {
        cin >> i;
    }
    cin >> m;
    box.resize(m);
    for (int& i : box) {
        cin >> i;
    }

    /*
    * 내림차순으로 배열하여 무게가 가장 무거운 것부터 할당한다.
    * 박스 무게가 크레인 최대 무게보다 크면 옮길 수 없다.
    */
    sort(crane.rbegin(), crane.rend());
    sort(box.rbegin(), box.rend());

    if (crane.front() < box.front()) {
        cout << -1;
    }
    else {
        int ans = 0;

        while (!box.empty()) {
            ans++;

            for (int i = 0; i < n; i++) {
                for (auto j = box.begin(); j != box.end(); j++) {
                    if (crane[i] >= *j) {
                        /*
                        * 크레인에 할당한 박스 제거.
                        */
                        box.erase(j);
                        break;
                    }
                }
            }
        }

        cout << ans;
    }

    return 0;
}