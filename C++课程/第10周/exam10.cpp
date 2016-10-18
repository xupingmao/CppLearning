#include <iostream>
#include <map>
using namespace std;
// 在此处补充你的代码

class A{

public:
	
	static int count;
	
	A()
	{
		// count++;
		count++;
	}
	A(int n)
	{
		// count++;
		count++;
	}
	virtual ~A()
	{
		count--;
		cout << "A::destructor" << endl;
	}
};

class B : public A{

public:
	
	B(int n)
	{
		// count++;
	}
	
	B(B& b)
	{
		//
		// cout << "copy constructor" << endl;
		// count++;
	}
	
	virtual ~B()
	{
		cout << "B::destructor" << endl;
	}
	/*
	void* operator new(size_t size)
	{
		// count-=2
		return malloc(size);
	}
	*/
};

// END
int A::count = 0;
void func(B b) { }
int main()
{
        A a1(5),a2;
        cout << A::count << endl; // 2
        B b1(4);
        cout << A::count << endl;  // 3
        func(b1);
        cout << A::count << endl;  // 3
        A * pa = new B(4);
        cout << A::count << endl;  // 4
        delete pa;
        cout << A::count << endl;  // 3
        return 0;
}
