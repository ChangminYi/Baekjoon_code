#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

struct circle {
    int dir, idx;
    bool is_left;
};

int n;
bool flag = true;
circle arg[400'000];
stack<int> stk;

bool cmp(const circle& lhs, const circle& rhs) {
    return lhs.dir < rhs.dir;
}

int main() {
    /**
     * 원의 양측 끝을 괄호로 치환하여 생각하면,
     * 옳은 괄호 문자열 문제로 생각할 수 있다. 따라서, 스택을 사용하여
     * 치환된 원들이 옳은 괄호 문자열을 이루고 있는지를 확인하면 된다.
     * 그리고 좌표 오름차순으로 정렬했을 때 같은 점에 두 괄호가 있으면 안된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0, x, r; i < 2 * n; i += 2) {
        cin >> x >> r;
        arg[i].dir = x - r, arg[i].idx = i, arg[i].is_left = true;
        arg[i + 1].dir = x + r, arg[i + 1].idx = i, arg[i + 1].is_left = false;
    }
    n <<= 1;

    sort(arg, arg + n, cmp);

    for(int i = 1; i < n && flag; i++) {
        if(arg[i].dir == arg[i - 1].dir)
            flag = false;
    }
    if(flag) {
        for(int i = 0; i < n && flag; i++) {
            if(arg[i].is_left)
                stk.push(arg[i].idx);
            else if(stk.top() != arg[i].idx)
                flag = false;
            else
                stk.pop();
        }
    }

    cout << (flag ? "YES" : "NO");

    return 0;
}