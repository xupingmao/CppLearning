#include<string>
#include<iostream>

using namespace std;

// string functions
// begin() return iterator
// end() return end


void TestIterator() {
    string::iterator i; // note this is a string::iterator
    string str = "test string";

    cout << "print by order" << endl;
    for (i = str.begin(); i != str.end(); ++i)
    {
        cout << *i;
    }

    cout << endl;

    cout << "print reverse" << endl;
    string::reverse_iterator ri;
    for (ri = str.rbegin(); ri != str.rend(); ++ ri)
    {
        cout << *ri;
    }
    cout << endl;

    cout << "const" << endl;
    // only supported in C++11
    for (auto ci = str.cbegin(); ci != str.cend(); ci++)
    {
        cout << *ci;
    }
    cout << endl;
}

void TestFuncs() {
    cout << endl << "TestFuncs" << endl;
    string abc = "new string";
    cout << "abc=" << abc << endl;
    cout << "abc.size()=" << abc.size() << endl;
    cout << "abc.length()=" << abc.length() << endl;
    cout << "abc.find(\"new\")=" << abc.find("new") << endl;
    cout << "abc.find(\"c\")=" << abc.find("c") << endl;
    cout << "string::npos=" << string::npos << endl;
}

int main(int argc, char const *argv[])
{
    string str = "test";

    cout << "hello,world, string value is " << str << endl;
    
    TestIterator();
    TestFuncs();
    return 0;
}
