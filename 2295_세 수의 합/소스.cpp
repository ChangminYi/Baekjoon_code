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
    * 두 수의 차를 인덱스로 사용하고, 그 값은 두 수 중 큰 값으로 저장.
    * argi[i]+argi[j]+argi[k]=argi[l]의 형태를
    * argi[i]+argi[j]=argi[l]-argi[k]로 변환
    */
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int idx = abs(argi[i] - argi[j]);
            max_val[idx] = max(argi[i], argi[j]);
        }
    }

    /*
    * 수의 중복이 가능하므로, j=i부터 시작.
    * 존재하는 값이 나올 경우 그 값으로 최댓값 갱신
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