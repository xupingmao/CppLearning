#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
	double dv;
	cin >> dv;
	
	
	
	int e = 0;
	
	double dv2 = dv;
	dv2 = abs(dv2);
	
	while (dv2 / 10.0f > 1.0f)
	{
		e++;
		dv2 /= 10;
	}
	
	while (dv2 < 1.0f)
	{
		e--;
		dv2 *= 10;
	}
	
	printf("%.5f\n", dv);
	if (e >= 0)
	{
		printf("%.7fe+%02d\n", dv2, e);
	}
	else
	{
		printf("%.7fe-%02d\n", dv2, abs(e));
	}
	
	return 0;
}
