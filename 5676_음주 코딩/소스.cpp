#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_LENG = 100001;

int n, k;
char segtree[4 * MAX_LENG + 1], argi[MAX_LENG];
string init_str;
stringstream strstm;

void init_segtree(int idx, int lo, int hi) {
    if (lo == hi) {
        segtree[idx] = argi[lo];
    }
    else {
        int mid = (lo + hi) / 2;
        init_segtree(2 * idx, lo, mid);
        init_segtree(2 * idx + 1, mid + 1, hi);

        if (segtree[2 * idx] == '0' || segtree[2 * idx + 1] == '0') {
            segtree[idx] = '0';
        }
        else {
            if (segtree[2 * idx] == segtree[2 * idx + 1]) {
                segtree[idx] = '+';
            }
            else {
                segtree[idx] = '-';
            }
        }
    }
}

void update_segtree(int idx, int lo, int hi, int argi_idx, char new_val) {
    if (lo == hi) {
        segtree[idx] = new_val;
    }
    else {
        int mid = (lo + hi) / 2;

        if (argi_idx <= mid) {
            update_segtree(2 * idx, lo, mid, argi_idx, new_val);
        }
        else {
            update_segtree(2 * idx + 1, mid + 1, hi, argi_idx, new_val);
        }

        if (segtree[2 * idx] == '0' || segtree[2 * idx + 1] == '0') {
            segtree[idx] = '0';
        }
        else {
            if (segtree[2 * idx] == segtree[2 * idx + 1]) {
                segtree[idx] = '+';
            }
            else {
                segtree[idx] = '-';
            }
        }
    }
}

char get_query(int idx, int lo, int hi, int s_lo, int s_hi) {
    if (lo == s_lo && hi == s_hi) {
        return segtree[idx];
    }
    else {
        int mid = (lo + hi) / 2;

        if (s_hi <= mid) {
            return get_query(2 * idx, lo, mid, s_lo, s_hi);
        }
        else if (mid < s_lo) {
            return get_query(2 * idx + 1, mid + 1, hi, s_lo, s_hi);
        }
        else {
            char res1 = get_query(2 * idx, lo, mid, s_lo, mid);
            char res2 = get_query(2 * idx + 1, mid + 1, hi, mid + 1, s_hi);

            if (res1 == '0' || res2 == '0') {
                return '0';
            }
            else {
                return (res1 == res2 ? '+' : '-');
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    std::cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 입력의 끝을 명시적으로 입력하지 않으므로,
    * getline을 사용하여 입력의 끝까지 받는다.
    * 받은 문자열은 stringstream을 이용하여 int형으로 파싱한다.
    */
    while (getline(cin, init_str)) {
        strstm.str(init_str);
        (strstm >> n >> k).clear();

        for (int i = 1, tmp; i <= n; i++) {
            cin >> tmp;
            argi[i] = (tmp == 0 ? '0' : (tmp > 0 ? '+' : '-'));
        }

        /*
        * 연산 결과의 부호에 대한 세그먼트 트리.
        * 출력의 편의성과 메모리 절약을 위해서 char로 선언하였다.
        * top-down 세그먼트 트리로 구현하였다.
        */
        init_segtree(1, 1, n);

        for (int i = 0; i < k; i++) {
            char inst;
            int arg1, arg2;
            (cin >> inst >> arg1 >> arg2).ignore();

            if (inst == 'C') {
                char new_val = (arg2 == 0 ? '0' : (arg2 > 0 ? '+' : '-'));
                update_segtree(1, 1, n, arg1, new_val);
            }
            else if (inst == 'P') {
                std::cout << get_query(1, 1, n, arg1, arg2);
            }
        }

        std::cout << '\n';
    }

    return 0;
}