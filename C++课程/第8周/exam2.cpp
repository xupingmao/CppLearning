#include <iostream>
#include <vector>
#include <map>
#include <iterator> 
#include <algorithm>
#include <cstdio>

using namespace std;

void unique_it(vector<int>& v) {
	vector<int> cp(v.begin(), v.end()); // copy elements
	v.clear(); //
	
	for (int i = 0; i < cp.size(); i++) {
		int value = cp[i];
		if (find(v.begin(), v.end(), value) == v.end()) {
			// 如果不包含在内 
			v.push_back(value);
		}
	}
}

class Input {
	public:
	string op;
	int id1;
	int id2;
	int value;
};

void GetInput(vector<Input> &v) {
	int n;
	cin >> n;
	string op;
	
	while (--n>=0) {
		cin >> op;
		Input input;
		
		input.op = op;
		
		if (op == "new") {
			cin >> input.id1;
		} else if (op == "add") {
			cin >> input.id1;
			cin >> input.value;
		} else if (op == "merge") {
			cin >> input.id1 >> input.id2;
		} else if (op == "unique") {
			cin >> input.id1;
		} else if (op == "out") {
			cin >> input.id1;
		}
		
		v.push_back(input);
	}
}

void PrintNewLine() {
	// static int n = 0;
	// if (n!=0) {
		// cout << endl;
		// printf("\n");
	// }
	// n++;
	cout << endl;
}

void PrintVector(vector<int> v) {
	/*
	if (v.size()==0) {
		return;
	}*/
	sort(v.begin(), v.end()); 
	for (int i = 0; i < v.size(); i++) {
		int value = v[i];
		// cout << value;
		// printf("%d ", value);
		cout << value << " ";
		// if (i != v.size() - 1) {
		// 	printf(" ");
		// }
	}
	PrintNewLine();
}

void HandleOperation(vector<Input>& inputVector) {
	map<int,vector<int> > my_map;
	
	for (int i = 0; i < inputVector.size(); i++) {
		Input &input = inputVector[i];
		string op = input.op;
		
		if (op == "new") {
			vector<int> v;
			my_map[input.id1] = v;
		} else if (op == "add") {
			my_map[input.id1].push_back(input.value);
		} else if (op == "merge") {
			if (input.id1 != input.id2) {
				vector<int> &v1 = my_map[input.id1];
				vector<int> &v2 = my_map[input.id2];
				v1.insert(v1.end(), v2.begin(), v2.end());
				v2.clear();
			}
		} else if (op == "unique") {
			vector<int> &v = my_map[input.id1];
			unique_it(v);
		} else if (op == "out") {
			vector<int> &v = my_map[input.id1];
			// printf("%04d: out %d ", i+1, input.id1);
			PrintVector(v);
		}
	}
}

int main() {
	string op;
	
	vector<Input> vector;
	
	GetInput(vector);
	HandleOperation(vector);
	
	return 0;
}
