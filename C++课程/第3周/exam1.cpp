#include <iostream>
using namespace std;
class A {
public:
    int val;
// 在此处补充你的代码

    A() {
        val = 0;
    }
    
    int& GetObj() {
        return val;
    }
};
int main(int argc, char** argv)  {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;
    return 0;
}