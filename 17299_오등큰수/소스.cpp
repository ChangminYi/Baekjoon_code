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

    // �Է��� �����鼭, ���ڰ� �� �� �����ϴ��� ����.
    for (int& i : arg) {
        cin >> i;
        cnt[i]++;
    }

    /*
    * �����ʺ��� �������� �����鼭 ������Ʈ.
    * �ڽź��� �����ʿ� �ִ� ���ҵ� �� ���� ���� �ڽź��� ���� �͵��� ���ʷ�
    * �����ϴ� ����, ������ ��ų� Ư�� ���� ã�´�. ������ ��� ����
    * ����ū���� -1�� ���, Ư�� ���� ã���� �� ���� ���� ���� ����ū��.
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