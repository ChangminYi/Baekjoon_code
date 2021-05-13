
#include <iostream>
#include <vector>
using namespace std;

typedef class NODE {
public:
	int value;
	bool isPoped;

	NODE() : value(0), isPoped(false) {}
}node;


int main() {
	vector<node> arg;
	int size = 0, index = 0/*현재 index*/, toGo = 0;

	cin >> size;
	arg = vector<node>(size);
	for (int i = 0, temp = 0; i < size; i++) {
		cin >> temp;
		arg[i].value = temp;
	}

	cout << index + 1 << ' ';
	for (int i = 0, temp = 0/*다음 index를 셈*/; i < size - 1; i++) {
		toGo = arg[index].value;
		arg[index].isPoped = true;

		if (toGo < 0) {
			for (int j = 0; j < toGo * (-1); j++) {
				temp--;
				if (temp == -1) {
					temp = size - 1;
				}
				if (arg[temp].isPoped == true) {
					j--;
				}
			}
		}
		else { //toGo > 0
			for (int j = 0; j < toGo; j++) {
				temp++;
				if (temp == size) {
					temp = 0;
				}
				if (arg[temp].isPoped == true) {
					j--;
				}
			}
		}

		cout << temp + 1;
		if (i < size - 1) {
			cout << ' ';
		}
		index = temp;
	}


	return 0;
}