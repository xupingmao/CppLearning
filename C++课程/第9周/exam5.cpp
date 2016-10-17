#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Fighter{
	
public:
	int id;
	int strength;
	
public:
	Fighter(int id, int strength)
	{
		this->id = id;
		this->strength = strength;
	}
	
};

bool operator < ( const Fighter & f1, const Fighter & f2)
{
    return f1.strength < f2.strength;
}

int main()
{
	int n;
	set<Fighter> members;
	
	cin >> n;
	
	members.insert(Fighter(1, 1000000000));
	
	while (--n >= 0)
	{
		// 保证实力值都不一样 
		int id, strength;
		cin >> id >> strength;
		
		Fighter f(id, strength);
		
		pair<set<Fighter>::iterator, bool> ret = members.insert(f);
		// 
		set<Fighter>::iterator up, low, r, target;
		
		r = ret.first;
		// r = lower_bound(members.begin(), members.end(), f);
		up = low = r;
		up ++;
		low--;
		if (r == members.begin())
		{
			target = up;
		}
		else if (up == members.end()) 
		{
			target = low;// 前面一个 
		}
		else 
		{
			int low_gap = f.strength - low->strength;
			int up_gap  = up->strength - f.strength;
			if (low_gap <= up_gap)
			{
				target = low;
			} else {
				target = up;
			}
		}
		cout << f.id << " " << target->id << endl;
		
	}
	// cout << f.id << " " << target->id << endl;

    return 0;
}
