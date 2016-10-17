#include <iostream>
#include <string>
using namespace std;
// �ڴ˴�������Ĵ���
template <class T>
class CMyistream_iterator{
	
private:
	istream* in;
	T last;
	
public:
	CMyistream_iterator(istream& cin)
	{
		in = &cin;
		cin >> last;
	}
	
	T operator* ()
	{
		return last;
	}
	CMyistream_iterator& operator++ (int v) // v��֮Ϊ��Ԫ(dummy) 
	{
		*in >> last;
		return *this;
	}
};

// END

int main()
{
    CMyistream_iterator<int> inputInt(cin);
    int n1,n2,n3;
    n1 = * inputInt; //���� n1
    int tmp = * inputInt;
    cout << tmp << endl;
    inputInt ++;
    n2 = * inputInt; //���� n2
    inputInt ++;
    n3 = * inputInt; //���� n3
    cout << n1 << "," << n2<< "," << n3 << endl;
    CMyistream_iterator<string> inputStr(cin);
    string s1,s2;
    s1 = * inputStr;
    inputStr ++;
    s2 = * inputStr;
    cout << s1 << "," << s2 << endl;
    return 0;
}
