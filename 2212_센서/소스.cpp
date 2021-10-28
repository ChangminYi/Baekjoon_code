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
    * 기지국이 n개 이상이라면, 각 센서 위치에 기지국을 위치시킨다.
    * 그러면 총 거리는 0이 된다.
    */
    if (n <= k) {
        cout << 0;
    }
    else {
        arg.resize(n);
        diff.resize(n - 1);

        /*
        * 센서의 위치를 받아, 정렬한다.
        * 그리고, 인접 센서와의 거리 차이를 계산하여 정렬한다.
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
        * k개를 어딘가의 센서의 좌표와 일치시키면,
        * 나머지 n-k개만큼의 센서를 k개의 센서가 부담하게 된다.
        * 그 때 발생하는 거리가 diff에 저장되어 있으니,
        * 작은 값부터 n-k개 더해주면 거리의 최소합이 나온다.
        */
        long long sum = 0;
        for (int i = 0; i < n - k; i++) {
            sum += diff[i];
        }

        cout << sum;
    }

    return 0;
}