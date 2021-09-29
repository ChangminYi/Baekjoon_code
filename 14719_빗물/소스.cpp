#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int h, w;
vector<int> height, left_max, right_max;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> h >> w;
    height.resize(w);
    left_max.resize(w);
    right_max.resize(w);
    for (int& i : height) {
        cin >> i;
    }

    /*
    * 자신의 왼쪽에서 가장 높은 높이와 오론쪽에서 가장 높은 높이를 구함.
    * 물은 그 두 값 중 작은 값을 높이로 갖게 된다.
    * 그러므로 물의 높이에서 자신의 높이를 뺀 값을 다 더하면 정답.
    */
    for (int i = 0, max_h = -1; i < w; i++) {
        max_h = max(max_h, height[i]);
        left_max[i] = max_h;
    }
    for (int i = w - 1, max_h = -1; i >= 0; i--) {
        max_h = max(max_h, height[i]);
        right_max[i] = max_h;
    }

    int res = 0;
    for (int i = 0; i < w; i++) {
        res += min(left_max[i], right_max[i]) - height[i];
    }

    cout << res;

    return 0;
}