#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

lli lo, hi, res;
vector<bool> divided;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> lo >> hi;
    divided.resize(hi - lo + 1, false);
    res = hi - lo + 1;

    /*
    * sqrt(hi)���� ���� ��� �������� ���Ͽ� �˻�
    * �������� �� �� lo���� ũ�ų� ���� �ּڰ��� ���Ͽ�
    * �� ���� ���� ���� ��� �ɷ��� (�����佺�׳׽��� ü)
    * �������ٸ� ī��Ʈ �����ش�.
    * ����� ������ ���� ������ ���̴�.
    */
    for (lli i = 2, base; i * i <= hi; (i == 2 ? i++ : i += 2)) { // Ȧ���� ���� ��귮 ����
        base = lo / (i * i);
        if (lo % (i * i) > 0) {
            base++;
        }

        while (base * (i * i) <= hi) {
            if (!divided[base * (i * i) - lo]) {
                divided[base * (i * i) - lo] = true;
                res--;
            }
            base++;
        }
    }

    cout << res;
    
    return 0;
}