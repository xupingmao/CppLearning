#include <iostream>
using namespace std;
// 在此处补充你的代码
class CType
{

public:
	int num;
	void setvalue(int n)
	{
		num = n;
	}
	
	CType operator++(int n)
	{
		CType old;
		old.setvalue(num);
		num = num * num;
		return old;
	}
};

ostream& operator<<(ostream& out, const CType& obj)
{
	out << obj.num;
	// out << obj.num * obj.num;
	return out;
}

// END

int main(int argc, char* argv[]) {
        CType obj;
        int n;
        cin>>n;
        while ( n ) {
                obj.setvalue(n);
                cout<<obj++<<" "<<obj<<endl;
                cin>>n;
        }
        return 0;
}
