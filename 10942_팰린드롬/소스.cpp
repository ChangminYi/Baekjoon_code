#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> argi;
vector<vector<bool>> is_palin;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n + 1);
    is_palin.resize(n + 1, vector<bool>(n + 1, false));
    for (int i = 1; i <= n; i++) {
        cin >> argi[i];
        is_palin[i][i] = true;  // ���� 1�� ������ �ݵ�� �Ӹ����
    }
    cin >> m;

    // �����ϴ� ���� �� ���� �Ӹ����
    for (int i = 1; i < n; i++) {
        if (argi[i] == argi[i + 1]) {
            is_palin[i][i + 1] = true;
        }
    }
    // ������ �Ӹ���� ������Ʈ
    for (int i = 2; i < n; i++) {
        for (int j = 1; j <= n - i; j++) {
            if (argi[j] == argi[j + i] && is_palin[j + 1][j + i - 1]) {
                is_palin[j][j + i] = true;
            }
        }
    }

    do {
        int lo, hi;
        cin >> lo >> hi;

        cout << (is_palin[lo][hi] ? 1 : 0) << '\n';
    } while (--m > 0);

    return 0;
}