#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:    
    double r,i;
public:    
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 在此处补充你的代码
	
	Complex& operator=(char* str) {
		char* newstr = new char[strlen(str)+1];
		strcpy(newstr, str);
		char* part1, *part2;
		part1 = strtok(newstr, "+");
		part2 = strtok(NULL, "+i");
		// cout << part1 << part2 << endl;
		r = atof(part1);
		i = atof(part2);
		delete[] newstr;
		return *this;
	}

};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}
