#include <iostream>

using namespace std;

int n;
int dist[20][20];
bool usable[20][20];

bool floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && i != k && j != k) {
                    if (dist[i][j] == dist[i][k] + dist[k][j]) {
                        usable[i][j] = false;
                    }
                    else if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
            usable[i][j] = true;
        }
    }

    /*
    * �÷��̵�-�ͼ� �˰����� �����ϸ鼭, ��� ������ �������� üũ.
    * �߰��� ����� �߻��ϸ� -1�� ����Ѵ�. ���ٸ�, ��� ������ ������
    * ����ġ�� ��� ���� �� ���.
    */
    if (floyd()) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (usable[i][j]) {
                    sum += dist[i][j];
                }
            }
        }
        cout << sum;
    }
    else {
        cout << -1;
    }

    return 0;
}