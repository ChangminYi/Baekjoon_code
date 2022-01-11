#include <iostream>
#include <map>

using namespace std;

int n, cnt = 0;
map<int, int> arg;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� h���� ǳ���� ���߸�, h-1�� ���̰� �������� ��� �����Ѵ�.
    * ����, ���� ��ġ ������ h+1�� ������ ǳ���� �ִٸ�, �� ǳ���� ����
    * ȭ���� ���� ��ġ�� ���߰� �� ���̴�. ���� �Է��� �����鼭 ǳ���� ����
    * �����ϰ�, ȭ���� ���� ��� ������Ʈ�ϸ� �ȴ�.
    */
    cin >> n;
    for (int i = 0, cur; i < n; i++) {
        cin >> cur;

        if (arg.find(cur) == arg.end()) {
            arg.insert(make_pair(cur, 1));
        }
        else {
            arg[cur]++;
        }

        if (arg.find(cur + 1) == arg.end()) {
            cnt++;
        }
        else {
            if (--arg[cur + 1] == 0) {
                arg.erase(cur + 1);
            }
        }
    }

    cout << cnt;

    return 0;
}