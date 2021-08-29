#include <iostream>
#include <cmath>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n, r, c;
	cin >> n >> r >> c;

	int res = 0;
	int tmp_col = (int)pow(2, n - 1);
	int tmp_row = tmp_col;
	while (n-- > 0) {
		int line_shift = (int)pow(2, n - 1);
		int block_size = (int)pow(4, n);

        if (tmp_col > c && tmp_row > r) {
			tmp_col -= line_shift;
			tmp_row -= line_shift;
        }
        else if (tmp_col <= c && tmp_row > r) {
			tmp_col += line_shift;
			tmp_row -= line_shift;
            res += block_size;
        }
        else if (tmp_col > c && tmp_row <= r) {
			tmp_col -= line_shift;
			tmp_row += line_shift;
            res += 2 * block_size;
        }
        else {
			tmp_col += line_shift;
			tmp_row += line_shift;
            res += 3 * block_size;
        }
	}

	cout << res;

	return 0;
}