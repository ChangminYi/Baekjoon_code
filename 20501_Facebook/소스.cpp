#include <iostream>
#include <bitset>

using namespace std;

int n, q, arg1, arg2;
bitset<2001> adj[2001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * long long ������ ��Ʈ�� ǥ���ص� ������,
    * stl�� �����ϴ� bitset�� Ȱ���ص� �ȴ�. �ӵ��� bitset�� �� ������.
    * �� ��������� AND�� ������� 1�� ��Ʈ�� ���� ���� �ȴ�.
    */

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> adj[i];
    }
    cin >> q;

    do {
        cin >> arg1 >> arg2;
        cout << (adj[arg1] & adj[arg2]).count() << '\n';
    } while (--q);

    return 0;
}