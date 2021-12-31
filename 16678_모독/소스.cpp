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
    * 명예 점수를 오름차순으로 정렬한다. 그리고 점수를 깎아야 하는지를 판단.
    * 1번부터 시작하여, 점수가 번호보다 높거나 같으면 점수를 깎아야 한다.
    * 따라서 점수와 번호의 차만큼을 총합에 더해주고, 번호를 올리면 된다.
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