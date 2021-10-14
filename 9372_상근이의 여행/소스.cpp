#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

int testcase, n, m;
pint tmp;

/*
* mst의 기본을 묻는 문제.
* 굳이 연결할 필요가 없으므로, mst의 크기인 n-1만 출력한다.
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