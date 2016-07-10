#include <iostream>
#include <set>

using namespace std;


int main(int argc, char **argv) {
	set<int> intSet;

	intSet.insert(10);
	intSet.insert(2);
	intSet.insert(12);
	intSet.insert(10);

	cout << "[";
	for (set<int>::iterator it = intSet.begin(); it != intSet.end(); it ++) {
		if (it != intSet.begin()) {
			cout << ",";
		}
		cout << *it;
	}
	cout << "]" << endl;
	return 0;
}


