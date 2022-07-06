#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct pos {
    int x, y, idx;
};

int n;
pos arg[50000];

long double get_tan(const pos& left, const pos& right) {
    long double x_diff = right.x - left.x;
    long double y_diff = right.y - left.y;
    return y_diff / x_diff;
}

bool cmp_x(const pos& lhs, const pos& rhs) {
    return lhs.x < rhs.x;
}

bool cmp_idx(const pos& lhs, const pos& rhs) {
    return lhs.idx < rhs.idx;
}

int main() {
    /**
     * 모든 좌표를 x 좌표 오름차순으로 정렬하고, 가장 큰 기울기의 값을 먼저 구한다.
     * 이 과정에서 가장 작은 인덱스도 같이 구한다. 입력 순으로 다시 좌표를 정렬하고,
     * 가장 작은 인덱스의 다음부터 탐색을 시작하여 가장 큰 기울기가 나오면 종료.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arg[i].x >> arg[i].y;
        arg[i].idx = i;
    }

    sort(arg, arg + n, cmp_x);

    long double max_tan = -1;
    int idx_a = INT32_MAX;
    for(int i = 0; i < n - 1; i++) {
        long double tmp_tan = abs(get_tan(arg[i], arg[i + 1]));
        if(max_tan < tmp_tan) {
            max_tan = tmp_tan;
            idx_a = min(arg[i].idx, arg[i + 1].idx);
        }
        else if(max_tan == tmp_tan) {
            idx_a = min(idx_a, min(arg[i].idx, arg[i + 1].idx));
        }
    }

    sort(arg, arg + n, cmp_idx);
    
    int idx_b = INT32_MAX;
    for(int i = idx_a + 1; i < n; i++) {
        long double tmp_tan = abs(get_tan(arg[idx_a], arg[i]));
        if(max_tan == tmp_tan) {
            idx_b = i;
            break;
        }
    }

    cout << idx_a + 1 << ' ' << idx_b + 1;

    return 0;
}