#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	vector<string> dog = {
		"|\\_/|\n",
		"|q p|   /}\n",
		"( 0 )\"\"\"\\\n",
		"|\"^\"`    |\n",
		"||_/=\\\\__|"
	};
	for (string &s : dog) {
		cout << s;
	}
	return 0;
}