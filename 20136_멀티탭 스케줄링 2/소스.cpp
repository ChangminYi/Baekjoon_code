#include <iostream>
#include <queue>
#include <map>
#include <functional>

using namespace std;

int n, k, cnt;
int arg[500'000];
bool plugged[500'001];
queue<int> use_seq[500'001];
multimap<int, int, greater<>> in_use;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �÷��׸� ����ϴ� ����� �� �� ������ ����� ���� ����.
    * ù ��°�� ���� ��ȣ�� �̹� �÷��׿� �ִ� ���. ������ ���� ��ȣ�� ������ ������ ������Ʈ�Ѵ�.
    * �� ��°�� ���� ��ȣ�� �÷��׿� ����, �÷��װ� ��� �� ���.
    * �� ���� ������ ���� ������ ���� ���� ��ȣ�� �����ϰ� �ڽ��� ����. �� �� ī��Ʈ�� �ö󰣴�.
    * �������� ���� ��ȣ�� �÷��׿� ����, �÷��׿� �� ĭ�� �ִ� ���. �ڱ� ��ȣ�� �����ϸ� �ȴ�.
    * ������ ������� ���� ��ȣ�� ���, �켱������ ��ĥ �� �־� multimap ���.
    */

    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        cin >> arg[i];
        use_seq[arg[i]].push(i);
    }

    for (int i = 0, cur_seq; i < k; i++) {
        cur_seq = use_seq[arg[i]].front();
        use_seq[arg[i]].pop();

        if (plugged[arg[i]]) {
            in_use.erase(cur_seq);
            in_use.insert(make_pair(use_seq[arg[i]].empty() ? INT32_MAX : use_seq[arg[i]].front(), arg[i]));
        }
        else {
            if (in_use.size() == n) {
                cnt++;
                plugged[in_use.begin()->second] = false;
                in_use.erase(in_use.begin());
            }
            plugged[arg[i]] = true;
            in_use.insert(make_pair(use_seq[arg[i]].empty() ? INT32_MAX : use_seq[arg[i]].front(), arg[i]));
        }
    }

    cout << cnt;

    return 0;
}