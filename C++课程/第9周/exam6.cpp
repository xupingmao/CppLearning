#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int ComputePrimeFactor(int n)
{
	int count = 0;
	int n2 = n;
	for(int i=2;i<=n2;i++){
		bool has = false;
        for(;n2%i==0;){ // i 可以被整除, 一直到n2不能被i整除
						// 能保证i是质数 
            n2=n2/i;   
			if (!has) 
            	count++;
            has = true;
            if (i == n)
            {
            	count--; // 不能等于自己 
			}
        }
    }
    if (n != 1)
    	count++; // 1.
    return count;
}

class Number{
	
public:
	int value;
	int prime_factor_cnt;
	
	
	Number(int n)
	{
		value = n;
		prime_factor_cnt = ComputePrimeFactor(n); 
	}
};

bool operator< (const Number& n1, const Number& n2)
{
	if (n1.prime_factor_cnt < n2.prime_factor_cnt) {
		return true;
	}
	if (n1.prime_factor_cnt == n2.prime_factor_cnt) {
		return n1.value < n2.value;
	}
	return false;
}

int main()
{
	int n;
	cin >> n;
	
	set<Number> v;
	
	
	while (--n >= 0)
	{
		int j = 0;
		while (j++<10)
		{
			int k ;
			cin >> k;
			// nqueue.push(Number(k));
			v.insert(Number(k));
		}
		set<Number>::iterator first, last;
		first = v.begin();
		last  = v.end();
		last --;
		cout << last->value << " "  << first->value << endl;
		v.erase(*first);
		v.erase(*last);
	}
	
	
    return 0;
}
