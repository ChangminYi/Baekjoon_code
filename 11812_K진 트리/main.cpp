#include <iostream>
#include <cmath>

using namespace std;

long long n, u, v;
int k, q;

long long get_depth(long long i) {
    int ret = 0;
    while(i) {
        i = (i - 1) / k, ret++;
    }
    return ret;
}

long long get_dist(long long n1, long long n2) {
    long long ret = 0;
    long long d1 = get_depth(n1), d2 = get_depth(n2);
    if(d1 > d2) {
        swap(n1, n2), swap(d1, d2);
    }

    while(d1 < d2) {
        ret++, d2--, n2 = (n2 - 1) / k;
    }
    while(n1 != n2) {
        ret += 2, n1 = (n1 - 1) / k, n2 = (n2 - 1) / k;
    }

    return ret;
}

int main() {
    /**
     * 1-base로 계산하면 복잡하므로, 0-base로 변환하여 계산한다.
     * i번 노드의 자식의 범위는 i * k + 1에서 i * (k + 1)까지이다.
     * 이를 역변환하여 노드의 높이를 구한 다음, 최소 공통 조상을 찾으면 된다.
     * 단, k = 1인 경우 이 방법으로는 시간초과가 나므로 예외처리를 해줘야 한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k >> q;

    if(k == 1) {
        do {
            cin >> u >> v;
            cout << abs(u - v) << '\n';
        } while(--q);
    }
    else {
        do {
            cin >> u >> v;
            cout << get_dist(u - 1, v - 1) << '\n';
        } while(--q);
    }

    return 0;
}
