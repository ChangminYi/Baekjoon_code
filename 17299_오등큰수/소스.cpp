#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct dat {
    int count = 0;
    int num = 0;
    dat(int c, int n) : count(c), num(n) {}
};
const int MAX = 1000000;

int n;
vector<int> arg, ngf;
int cnt[MAX + 1] = { 0 };
stack<dat> stk;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n);
    ngf.resize(n);

    // 입력을 받으면서, 숫자가 몇 번 등장하는지 센다.
    for (int& i : arg) {
        cin >> i;
        cnt[i]++;
    }

    /*
    * 오른쪽부터 왼쪽으로 훑으면서 업데이트.
    * 자신보다 오른쪽에 있는 원소들 중 등장 수가 자신보다 낮은 것들을 차례로
    * 제거하다 보면, 스택이 비거나 특정 값을 찾는다. 스택이 비는 경우는
    * 오등큰수가 -1인 경우, 특정 값을 찾으면 그 값이 나온 수가 오등큰수.
    */
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && cnt[arg[i]] >= stk.top().count) {
            stk.pop();
        }

        ngf[i] = (stk.empty() ? -1 : stk.top().num);
        stk.push(dat(cnt[arg[i]], arg[i]));
    }

    for (const int& i : ngf) {
        cout << i << ' ';
    }

    return 0;
}