#include <iostream>
#include <vector>

using namespace std;

int n, t;
vector<int> degree;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    degree.resize(n + 1);
    for (int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        degree[a]++, degree[b]++;
    }

    cin >> t;
    for (int i = 0, inst, arg; i < t; i++) {
        cin >> inst >> arg;

        if (inst == 1) {
            /*
            * Ʈ��������, ����� ��尡 2�� �̻��̸� �ݵ�� ������.
            * ����Ŭ�� �������� �ʱ� ����.
            */
            cout << (degree[arg] <= 1 ? "no\n" : "yes\n");
        }
        else {
            /*
            * ����Ŭ�� ���� ������, Ʈ���� ��� ������ ������.
            */
            cout << "yes\n";
        }
    }

    return 0;
}