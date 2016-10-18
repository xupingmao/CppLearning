#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class A{

public:
	int age;
	string name;
	
	A()
	{
	}
	
	A(int age)
	{
		name = "A";
		this->age = age;
	}
};

class B : public A{

public:
	B(int age)
	{
		name = "B";
		this->age = age;
	}
};


class Comp{
public:
	bool operator() (const A* a, const A* b)
	{
		return a->age < b->age;
	}
};

void Print(const A* a)
{
	cout << a->name << " " << a->age << endl;
}

// END
int main()
{

        int t;
        cin >> t;
        set<A*,Comp> ct;
        while( t -- ) {
                int n;
                cin >> n;
                ct.clear();
                for( int i = 0;i < n; ++i)	{
                        char c; int k;
                        cin >> c >> k;

                        if( c == 'A')
                                ct.insert(new A(k));
                        else
                                ct.insert(new B(k));
                }
                for_each(ct.begin(),ct.end(),Print);
                cout << "****" << endl;
        }
}
