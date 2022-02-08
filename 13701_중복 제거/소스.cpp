#include <iostream>

using namespace std;

int n, visit_bit;
uint32_t visit[1 << 20];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 입력의 수를 명시하지 않았으므로, 입력이 끝날 때까지 받는다.
    * 메모리에 저장된 비트 하나하나를 bool형으로 생각한다.
    * 비트가 1이면 이미 나온 숫자이고, 0이라면 아직 나오지 않은 숫자이다.
    * 각 숫자마다 이전에 나왔는지를 비트 연산으로 체크하고, 나오지 않았다면
    * 출력한 다음에 비트를 1로 설정해준다.
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