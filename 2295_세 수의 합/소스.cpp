#include <iostream>
#include <vector>
#include <map>

using namespace std;

int n;
vector<int> argi;
map<int, int> max_val;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n);
    for (int& i : argi) {
        cin >> i;
    }

    /*
    * �� ���� ���� �ε����� ����ϰ�, �� ���� �� �� �� ū ������ ����.
    * argi[i]+argi[j]+argi[k]=argi[l]�� ���¸�
    * argi[i]+argi[j]=argi[l]-argi[k]�� ��ȯ
    */
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int idx = abs(argi[i] - argi[j]);
            max_val[idx] = max(argi[i], argi[j]);
        }
    }

    /*
    * ���� �ߺ��� �����ϹǷ�, j=i���� ����.
    * �����ϴ� ���� ���� ��� �� ������ �ִ� ����
    */
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int idx = argi[i] + argi[j];

            if (max_val.find(idx) != max_val.end()) {
                res = max(max_val[idx], res);
            }
        }
    }

    cout << res;

    return 0;
}