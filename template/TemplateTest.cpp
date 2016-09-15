/*************************************************************************
	> File Name: TemplateTest.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Mar 14 11:13:01 2016
 ************************************************************************/

#include<iostream>
using namespace std;


/**
 *  grammar
 * template <typename | class T> function_decl 
 * template <class | class T> class_decl; 
 */

// T is function template
template <typename T>
// printObject is a template function
void printObject(T t) {
    cout << "sizeof(T)=" << sizeof(T) << endl;
    cout << "value=" << t << endl;
}

template <class A>
void add (A a, A b) {
    cout << a << " + " << b << " = " << a + b << endl;
}

template <class T>
void MySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main(int argc, char* argv[]) {
    printObject(1);
    printObject(2);
    printObject("string");
    printObject('c');

    add(1, 2);
    add(1.1, 2.2);
    string a = "hello";
    string b = "world";
    add(a, b);

    cout << "test swap" << endl;
    int ia = 10;
    int ib = 20;
    cout << ia << ib << endl;
    MySwap(ia,ib);
    cout << ia << ib << endl;
}
