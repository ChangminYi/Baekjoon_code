#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> arg, diff;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    
    /*
    * �������� n�� �̻��̶��, �� ���� ��ġ�� �������� ��ġ��Ų��.
    * �׷��� �� �Ÿ��� 0�� �ȴ�.
    */
    if (n <= k) {
        cout << 0;
    }
    else {
        arg.resize(n);
        diff.resize(n - 1);

        /*
        * ������ ��ġ�� �޾�, �����Ѵ�.
        * �׸���, ���� �������� �Ÿ� ���̸� ����Ͽ� �����Ѵ�.
        */
        for (int& i : arg) {
            cin >> i;
        }
        sort(arg.begin(), arg.end());

        for (int i = 0; i < n - 1; i++) {
            diff[i] = arg[i + 1] - arg[i];
        }
        sort(diff.begin(), diff.end());

        /*
        * k���� ����� ������ ��ǥ�� ��ġ��Ű��,
        * ������ n-k����ŭ�� ������ k���� ������ �δ��ϰ� �ȴ�.
        * �� �� �߻��ϴ� �Ÿ��� diff�� ����Ǿ� ������,
        * ���� ������ n-k�� �����ָ� �Ÿ��� �ּ����� ���´�.
        */
        long long sum = 0;
        for (int i = 0; i < n - k; i++) {
            sum += diff[i];
        }

        cout << sum;
    }

    return 0;
}