#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

int testcase, n, m;
pint tmp;

/*
* mst�� �⺻�� ���� ����.
* ���� ������ �ʿ䰡 �����Ƿ�, mst�� ũ���� n-1�� ����Ѵ�.
*/
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    do {
        cin >> n >> m;
        
        for (int i = 0; i < m; i++) {
            cin >> tmp.first >> tmp.second;
        }

        cout << n - 1 << '\n';
    } while (--testcase > 0);

    return 0;
}