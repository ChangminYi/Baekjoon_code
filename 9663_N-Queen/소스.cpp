#include <iostream>
#include <vector>

using namespace std;

int n, cnt = 0;
vector<int> queen;

/*
* ���� ���� ���� ���� ���� �̹� �ٸ� ���� ���� ��ġ�ų�,
* �ٸ� ���� �밢���� �ִٸ� ���� �� ����.
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
* queen[i]�� i�࿡ �ִ� ���� �� ��ȣ�̴�.
* ������ ���� �ϳ��� ���� ���Ƽ� �����ϴٸ� ���� ������ ���� ���� �ݺ�
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