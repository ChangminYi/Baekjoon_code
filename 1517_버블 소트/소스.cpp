#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

int n;
vector<int> arg, merge_arg;

lli merge_sort(int lo, int hi) {
    if (lo == hi) {
        return 0;
    }
    else {
        int mid = (lo + hi) / 2;
        lli res = merge_sort(lo, mid) + merge_sort(mid + 1, hi);

        // �κ� �迭 ����. �������� ���� ���� ���Ѵ�.
        for (int i = lo, j = mid + 1, idx = 0; i <= mid || j <= hi; ) {
            if (i <= mid && (j > hi || arg[i] <= arg[j])) {
                merge_arg[idx++] = arg[i++];
            }
            else {
                res += (1LL + mid) - i;
                merge_arg[idx++] = arg[j++];
            }
        }

        // ���ĵ� �κ� �迭 ���� �迭�� �����
        for (int i = lo; i <= hi; i++) {
            arg[i] = merge_arg[i - lo];
        }

        return res;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n), merge_arg.resize(n);
    for (int& i : arg) {
        cin >> i;
    }

    /*
    * ���� ������ Ȱ���Ͽ� ������ ����. ������ ���׸�Ʈ Ʈ���� ����� ����.
    * ���ĵ� ������ ��ü �迭��, �� �迭�� ������ ���� �� �迭�� �ִٰ� �ϸ�,
    * ���� ���Ҹ� ���� ���� �������� ���� ���� ���Ŀ����� ���� Ƚ���� ����.
    * ��������� ������ �����ϸ� �׶����� Ƚ�� ���.
    */
    cout << merge_sort(0, n - 1);

    return 0;
}