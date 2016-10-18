#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
	int nGroup;
	cin >> nGroup;
	while (--nGroup>=0)
	{ 
		int k, n, i, j;
		k = 0;
		cin >> n >> i >> j;
		int ni = (n >> (i)) & 1;
		int nj = ((n >> (j)) & 1 ^ 1);
		int mid = 0;
		for (int ii = i + 1; ii < j; ii++)
		{
			mid += 1 << (ii  );
		}
		k += ni << (i );
		k += nj << (j );
		k += mid;
		printf("%x\n", k);
	}

    return 0;
}
