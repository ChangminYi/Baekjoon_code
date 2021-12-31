#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

long long sum = 0;
int n, cnt = 1;
vector<int> arg;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n);
    for (int& i : arg) {
        cin >> i;
    }

    /*
    * �� ������ ������������ �����Ѵ�. �׸��� ������ ��ƾ� �ϴ����� �Ǵ�.
    * 1������ �����Ͽ�, ������ ��ȣ���� ���ų� ������ ������ ��ƾ� �Ѵ�.
    * ���� ������ ��ȣ�� ����ŭ�� ���տ� �����ְ�, ��ȣ�� �ø��� �ȴ�.
    */
    sort(arg.begin(), arg.end());
    for (const int i : arg) {
        if (i >= cnt) {
            sum += i - cnt++;
        }
    }

    cout << sum;

    return 0;
}