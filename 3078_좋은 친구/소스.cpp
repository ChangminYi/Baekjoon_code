#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MIN_LENGTH = 2;
const int MAX_LENGTH = 20;

int n, k;
long long ans;
string tmp;
vector<int> arg[21];

long long get_set(int idx) {
    long long ret = 0, leng;
    int hi = 0;
    for (int i = 0; i < (int)arg[idx].size(); i++) {
        while (hi < (int)arg[idx].size() && arg[idx][hi] - arg[idx][i] <= k) {
            hi++;
        }
        ret += hi - i - 1;
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 이름의 길이를 인덱스로 삼아, 각 길이에서의 등수만을 저장한다.
    * 따라서 이름의 길이마다 등수는 오름차순으로 정렬된 상태로 유지된다.
    * 가장 작은 등수를 기준점으로 잡고, 기준값보다 k만큼 더 큰 값까지 탐색.
    * 기준점을 하나씩 증가시켜서 반복하고, 그 때의 수를 세어서 모두 더하면 정답.
    */

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        arg[tmp.length()].push_back(i);
    }

    for (int i = MIN_LENGTH; i <= MAX_LENGTH; i++) {
        ans += get_set(i);
    }

    cout << ans;

    return 0;
}