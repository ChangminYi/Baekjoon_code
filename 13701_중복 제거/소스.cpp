#include <iostream>

using namespace std;

int n, visit_bit;
uint32_t visit[1 << 20];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �Է��� ���� ������� �ʾ����Ƿ�, �Է��� ���� ������ �޴´�.
    * �޸𸮿� ����� ��Ʈ �ϳ��ϳ��� bool������ �����Ѵ�.
    * ��Ʈ�� 1�̸� �̹� ���� �����̰�, 0�̶�� ���� ������ ���� �����̴�.
    * �� ���ڸ��� ������ ���Դ����� ��Ʈ �������� üũ�ϰ�, ������ �ʾҴٸ�
    * ����� ������ ��Ʈ�� 1�� �������ش�.
    */

    while (cin >> n) {
        uint32_t &visit_block = visit[n / 32];
        visit_bit = 1 << (n % 32);
        if (visit_block & visit_bit) {
            continue;
        }
        else {
            cout << n << ' ';
            visit_block |= visit_bit;
        }
    }

    return 0;
}