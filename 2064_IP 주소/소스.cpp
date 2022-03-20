#include <iostream>
#include <bitset>

using namespace std;

int n;
char tmp;
bitset<32> nmask, arg[1'000];

bool has_same_networt(const bitset<32>& nmask) {
    bitset<32> nw = arg[0] & nmask;
    for (int i = 1; i < n; i++) {
        if ((arg[i] & nmask) != nw) return false;
    }
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 서브넷 마스크를 모두 1로 set한 후, 모든 주소의 
    * 네트워크 주소가 같아질 때까지 서브넷 마스크의 크기를 계속 늘리면 된다.
    */

    cin >> n;
    for (int i = 0, n1, n2, n3, n4; i < n; i++) {
        cin >> n1 >> tmp >> n2 >> tmp >> n3 >> tmp >> n4;
        arg[i] = (n1 << 24) | (n2 << 16) | (n3 << 8) | n4;
    }

    nmask.set();
    for (int i = 0; i < 32; i++) {
        if (has_same_networt(nmask)) break;
        else nmask[i] = false;
    }

    int nw = (nmask & arg[0]).to_ulong();
    int nm = nmask.to_ulong();
    cout << ((nw & 0xff000000) >> 24) << '.' << ((nw & 0x00ff0000) >> 16) << '.' << ((nw & 0x0000ff00) >> 8) << '.' << (nw & 0x000000ff) << '\n';
    cout << ((nm & 0xff000000) >> 24) << '.' << ((nm & 0x00ff0000) >> 16) << '.' << ((nm & 0x0000ff00) >> 8) << '.' << (nm & 0x000000ff);

    return 0;
}