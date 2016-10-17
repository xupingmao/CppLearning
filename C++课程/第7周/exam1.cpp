#include <iostream>
using namespace std;
// 在此处补充你的代码

template <class T>
class CArray3D
{
	private:
		T*** values;
		int xsize;
		int ysize;
		int zsize;
		
	public:
		
		CArray3D(int x, int y, int z)
		{
			xsize = x;
			ysize = y;
			zsize = z;
			values = new T**[x];
			for (int j = 0; j < x; j++)
			{
				T** temp = new T*[y];
				values[j] = temp;
				for (int k = 0; k < y; k++)
				{
					T* temp2 = new T[z];
					temp[k] = temp2;
				}
			}
		}
		
		~CArray3D ()
		{
			for (int j = 0; j < xsize; j++)
			{
				T** temp = values[j];
				for (int k = 0; k < ysize; k++)
				{
					delete temp[k];
				}
				delete temp;
			}
			delete values;
		}
		
		T** operator[] (int index)
		{
			return values[index];
		}
};

// END 
int main()
{
    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                cout << a[i][j][k] << ",";
return 0;
}
