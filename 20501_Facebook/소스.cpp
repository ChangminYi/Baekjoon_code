#include <iostream>
#include <bitset>

using namespace std;

int n, q, arg1, arg2;
bitset<2001> adj[2001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * long long 형으로 비트를 표현해도 되지만,
    * stl에 존재하는 bitset을 활용해도 된다. 속도는 bitset이 더 빠르다.
    * 두 인접행렬을 AND한 결과에서 1인 비트의 수를 세면 된다.
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