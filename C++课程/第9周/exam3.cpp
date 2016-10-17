#include <set>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    multiset<int> group;
    set<int> history;
    
    int n ;
    
    cin >> n;
    
    while (n-->0)
    {
    	string op;
    	int v;
    	cin >> op >> v;
    	if ("add" == op)
    	{
    		group.insert(v);
    		history.insert(v);
    		int count = group.count(v);
			// int count = group.end() - it;
    		cout << count << endl;
		}
		else if ("ask" == op)
		{
			// multiset<int>::iterator it = group.find(v);
			set<int>::iterator it = history.find(v);
			
			int count = group.count(v);
			
			if (it == history.end())
			{
				cout << "0 " << count << endl;
			}
			else 
			{
				cout << "1 " << count << endl;
			}
			/*
			for ( ; it != group.end(); it++)
			{
				cout << *it << " " ;
			}
			cout << endl;
			*/
		}
		else if ("del" == op)
		{
			cout << group.count(v) << endl;
			group.erase(v);
		}
	}
    
    return 0;
}
