#include <iostream>
#include <map>
#include <cmath>

using namespace std;

const int MIN = 0;
const int MAX = 300001;

int n, root;
map<int, int>::iterator ub, lb;
long long cnt = 0;
map<int, int> tree = {
    pair<int, int>(MIN, 0),
    pair<int, int>(MAX, 0)
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ������ �ǻ� �ڵ带 �״�� �����ϸ� �ð��ʰ�. skewed ������ ���� Ʈ���� ���´�.
    * map�� �̿��Ͽ� ��� ��ȣ�� �� ����� ���̸� �����Ѵ�. ��� ��ȣ�� �����ϹǷ�,
    * upper_bound�� ����Ͽ� �ٷ� ���� ���� ��带 ���ϰ�, ���� ���� ��嵵 ���Ѵ�.
    * ��尡 ���ԵǴ� ���̴� ����, ���� ����� ������ �ִ� + 1�̴�.
    */
    cin >> n >> root;
    tree.insert(make_pair(root, 0));
    cout << 0 << '\n';
    for (int i = 1, cur_node, cur_depth; i < n; i++) {
        cin >> cur_node;
        ub = tree.upper_bound(cur_node);
        lb = ub; --lb;
        cur_depth = max(ub->second, lb->second) + 1;
        tree.insert(make_pair(cur_node, cur_depth));
        
        cnt += cur_depth;
        cout << cnt << '\n';
    }

    return 0;
}