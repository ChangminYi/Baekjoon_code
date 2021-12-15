#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, m;
int prev_s[1000001], next_s[1000001];
int buf[500000];

void insert_station(const int pivot, const int added) {
    int left = pivot, right = next_s[pivot];
    next_s[left] = added, next_s[added] = right;
    prev_s[right] = added, prev_s[added] = left;
}

void erase_station(const int to_erase) {
    int left = prev_s[to_erase], right = next_s[to_erase];
    next_s[left] = right;
    prev_s[right] = left;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> buf[i];
    }

    /*
    * 더블 링크드 리스트를 구현한다. 2호선은 원형으로 연결되어 있으므로
    * 첫 번째 원소와 마지막 원소도 서로 이어줘야 한다.
    */
    prev_s[buf[0]] = buf[n - 1];
    next_s[buf[n - 1]] = buf[0];
    for (int i = 0; i < n - 1; i++) {
        prev_s[buf[i + 1]] = buf[i];
        next_s[buf[i]] = buf[i + 1];
    }

    /*
    * 명령에 따라 쿼리 실행.
    */
    do {
        string inst;
        cin >> inst;

        if (inst[0] == 'B') {
            int arg0, arg1;
            cin >> arg0 >>  arg1;

            if (inst[1] == 'N') {
                cout << next_s[arg0] << '\n';
                insert_station(arg0, arg1);
            }
            else {
                cout << prev_s[arg0] << '\n';
                insert_station(prev_s[arg0], arg1);
            }
        }
        else {
            int arg;
            cin >> arg;

            if (inst[1] == 'N') {
                cout << next_s[arg] << '\n';
                erase_station(next_s[arg]);
            }
            else {
                cout << prev_s[arg] << '\n';
                erase_station(prev_s[arg]);
            }
        }
    } while (--m);

    return 0;
}