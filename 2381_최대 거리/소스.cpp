#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> arg_add, arg_sub;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;

    arg_add.resize(n);
    arg_sub.resize(n);
    for (int i = 0, a, b; i < n; i++) {
        cin >> a >> b;

        arg_add[i] = a + b;
        arg_sub[i] = a - b;
    }

    /*
    * |a - c| + |b - d|의 절댓값을 풀면,
    * +-((a + b) - (c + d)) 혹은 +-((a - b) - (c - d))
    * 꼴이 나온다. 그러므로 +와 -를 각각 저장하여
    * arg[n - 1] - arg[0]이 가장 큰 값을 출력하면 된다.
    */
    sort(arg_add.begin(), arg_add.end());
    sort(arg_sub.begin(), arg_sub.end());
    cout << max(arg_add[n - 1] - arg_add[0], arg_sub[n - 1] - arg_sub[0]);

    return 0;
}