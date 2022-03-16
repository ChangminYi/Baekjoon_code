#include <iostream>

using namespace std;

int n;
int arg[1'000'000], buf[1'000'000];

long long merge_sort(const int lo, const int hi) {
    if (lo == hi) return 0;
    else {
        int mid = (lo + hi) / 2;
        long long ret = merge_sort(lo, mid) + merge_sort(mid + 1, hi);

        for (int i = lo, j = mid + 1, idx = lo; idx <= hi; idx++) {
            if (i <= mid && (j > hi || arg[i] < arg[j])) {
                buf[idx] = arg[i++];
            }
            else {
                ret += mid - i + 1;
                buf[idx] = arg[j++];
            }
        }

        for (int i = lo; i <= hi; i++) {
            arg[i] = buf[i];
        }
        return ret;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ū ���� ���� �ͺ��� �տ� �� �ִ� ��� ��츦 ���� �Ѵ�.
    * ���������� �� ��, �� ���� ���ĵ� �κ� �迭����, ���� �迭�� ����
    * ���� �迭�� ������ �۴ٸ� �̴� ������ �ڹٲ� ���̴�. ���� �� ��
    * ���� �κ� �迭�� ���� ������ ���� ��� ���ϸ� ��ü ���� ���� �� �ִ�.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
    }

    cout << merge_sort(0, n - 1);

    return 0;
}