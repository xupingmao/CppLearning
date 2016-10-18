#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// �ڴ˴�������Ĵ���
class CMy_add{	

public:
	int& sum;
	
	CMy_add(int& _sum)
	: sum(_sum)
	{
	
	} 
	
	void operator()(int v)
	{
		sum += v & 0x7;
	}
};
// END

int main(int argc, char* argv[]) {
        int v, my_sum=0;
        vector<int> vec;
        cin>>v;
        while ( v ) {
                vec.push_back(v);
                cin>>v;
        }
        for_each(vec.begin(), vec.end(), CMy_add(my_sum));
        cout<<my_sum<<endl;
        return 0;
}

