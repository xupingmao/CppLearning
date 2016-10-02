#include <iostream>
#include <cstring>
using namespace std;
// 在此处补充你的代码

class Array2 {
	private:
		int* values;
		int cols;
		int rows;
	public:
		Array2(int rows, int cols) {
			values = new int[rows * cols];
			this->rows = rows;
			this->cols = cols;
		}
		
		Array2() {
			cols = 0;
			rows = 0;
			values = NULL;
		}
		
		~Array2 () {
			if (values != NULL) {
				delete[] values;
			}
		}
		
		Array2& operator=(Array2& b) {
			this->rows = b.rows;
			this->cols = b.cols;
			this->values = new int(rows * cols);
			for (int i = 0; i < rows * cols; i++) {
				this->values[i] = b.values[i];
			}
		}
		
		int operator()(int x, int y) {
			return values[x * cols + y];
		}
		int* operator[](int x) {
			return values + x * cols;
		}
};

int main() {
    Array2 a(3,4);
    int i,j;
    for( i = 0;i < 3; ++i )
        for( j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b; b = a;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
