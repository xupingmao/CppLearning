#include<iostream>
using namespace std;
class Number {
public:
    int num;
    Number(int n=0): num(n) {}
// �ڴ˴�������Ĵ���
	
	Number operator*(Number& n)
	{
		return Number(num*n.num);
	}
	
	operator int()
	{
		return num;
	}
// END
};

int main() {
    Number n1(10), n2(20);
    Number n3;n3 = n1*n2;
    cout << int(n3) << endl;
    return 0;
}
