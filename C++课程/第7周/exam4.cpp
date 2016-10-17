#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

vector<string> g_group;


class Result{
	public:
		int n;
		string s;
};


Result Execute(string& op);

int ReadPositiveNum(string& s)
{
	for (int i = 0; i < s.size(); i++)
	{
		char c = s[i];
		if (c >= '0' && c <= '9')
		{
			continue;
		}
		else{
			return -1;
		}
	}
	int n = atoi(s.c_str());
	if (n > 99999)
	{
		return -1;
	}
	return n;
}

int ReadNum()
{
	string op;
	cin >> op;
	if (op == "find" || op == "rfind")
	{
		Result r = Execute(op);
		return r.n;
	}
	int n = atoi(op.c_str());
	return n;
}

string ReadStr()
{
	string op;
	cin >> op;
	if (op == "copy" || op == "add")
	{
		Result r = Execute(op);
		return r.s;
	}
	return op;
}

Result Execute(string& op)
{
	Result r;
	if (op == "find")
	{
		string s;
		int n;
		s = ReadStr();
		n = ReadNum();
		
		string &v = g_group[n-1];
		string::size_type pos =  v.find(s);
		if (pos == string::npos)
		{
			r.n = v.size();
		}
		else
		{
			r.n = pos;
		}
	}
	else if (op == "rfind")
	{
		string s;
		int n;
		s = ReadStr();
		n = ReadNum();
		string &v = g_group[n-1];
		string::size_type pos =  v.find_last_of(s);
		if (pos == string::npos)
		{
			r.n = v.size();
		}
		else
		{
			r.n = pos;
		}
	}
	else if (op == "copy")
	{
		int n, x, l;
		n = ReadNum();
		x = ReadNum();
		l = ReadNum();
		string v = g_group[n-1];
		// cout << v.substr(x, l) << endl;
		r.s = v.substr(x,l);
	}
	else if (op == "add")
	{
		string s1, s2;
		s1 = ReadStr();
		s2 = ReadStr();
		int n1 = ReadPositiveNum(s1);
		int n2 = ReadPositiveNum(s2);
		if (n1 >= 0 && n2 >= 0)
		{
			int n = n1 + n2;
			char buf[20];
			sprintf(buf, "%d", n);
			r.s = buf;
		}
		else
		{
			r.s = s1 + s2;
		}
	}
	else if (op == "insert")
	{
		string s;
		int n, x;
		s = ReadStr();
		n = ReadNum();
		x = ReadNum();
		
		g_group[n-1].insert(x, s);
	}
	else if ("reset" == op)
	{
		string s;
		int n;
		s = ReadStr();
		n = ReadNum();
		 
		g_group[n-1] = s;
	}
	else if ("print" == op)
	{
		int n;
		n = ReadNum();
		
		cout << g_group[n-1] << endl;
	}
	else if ("printall" == op)
	{
		for (int i = 0; i < g_group.size(); i++)
		{
			cout << g_group[i]  << endl;
		}
	}
	return r;
}

int main()
{
	int n;
	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		string temp;
		cin >> temp;
		g_group.push_back(temp);
	}
	
	string op;
	cin >> op;
	while (op != "over")
	{
		Execute(op);
		cin >> op;
	}
	return 0;
}
