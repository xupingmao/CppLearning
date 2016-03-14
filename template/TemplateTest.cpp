/*************************************************************************
	> File Name: TemplateTest.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Mar 14 11:13:01 2016
 ************************************************************************/

#include<iostream>
using namespace std;

template <typename T>

void printObject(T t) {
    cout << "sizeof(T)=" << sizeof(T) << endl;
    cout << "value=" << t << endl;
}

int main(int argc, char* argv[]) {
    printObject(1);
    printObject(2);
    printObject("string");
    printObject('c');
}
