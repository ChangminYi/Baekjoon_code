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
    * ������������ �迭�Ͽ� ���԰� ���� ���ſ� �ͺ��� �Ҵ��Ѵ�.
    * �ڽ� ���԰� ũ���� �ִ� ���Ժ��� ũ�� �ű� �� ����.
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
                        * ũ���ο� �Ҵ��� �ڽ� ����.
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