#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> argi;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n);
    for (int& i : argi) {
        cin >> i;
    }
    sort(argi.begin(), argi.end());

    int res = 0;
    for (int i = 0; i < n; i++) {
        int left = 0, right = n - 1;

        while (left < right) {
            int tmp_sum = argi[left] + argi[right];

            if (tmp_sum == argi[i]) {
                if (left != i && right != i) {
                    res++;
                    break;
                }
                else if (left == i) {
                    left++;
                }
                else if (right == i) {
                    right--;
                }
            }
            else if (tmp_sum < argi[i]) {
                left++;
            }
            else {
                right--;
            }
        }
    }

    cout << res;

    return 0;
}