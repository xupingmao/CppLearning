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

    cout << endl << "** string::find" << endl;
    cout << "abc.find(\"new\")=" << abc.find("new") << endl;
    cout << "abc.find(\"c\")=" << abc.find("c") << endl;
    cout << "string::npos=" << string::npos << endl;
    cout << "abc.find(\"n\",1)=" << abc.find("n", 1) << endl;


    cout << endl << "** string::replace" << endl;
    string str = "abc is abc is abc";
    cout << "str=" << str << endl;
    cout << "str.find_first_of(\"abc\")=" << str.find_first_of("abc") << endl;
    cout << "str.find_last_of(\"abc\")=" << str.find_last_of("abc") << endl;

    // replace
    // this is different from the `replace` method in script languages.
    cout << "str.replace(0, 3, \"cde\")=" << str.replace(0,3,"cde") << endl;
    cout << "str.replace(str.begin(), str.begin()+4, \"hhh\")=" << 
        str.replace(str.begin(), str.begin() + 4, "hhh") << endl;

    cout << endl << "** string::append" << endl;
    str = "hello";
    cout << "str=" << str << endl;
    cout << "str.append(\",\")=" << str.append(",") << endl;
    cout << "str.append(\"world\")=" << str.append("world") << endl;

    cout << endl << "** string::insert" << endl;
    str = "hello";
    cout << "str=" << str << endl;
    cout << "str.insert(1, \"**\")=" << str.insert(1, "**") << endl;

    cout << endl << "** string::substr" << endl;
    str = "hello";
    cout << "str=" << str << endl;
    cout << "str.substr(1,2)=" << str.substr(1,2) << endl;
    cout << "str.substr(2)=" << str.substr(2) << endl;

    cout << endl << "** string::data" << endl;
    str = "hello";
    cout << "str=" << str << endl;
    cout << "str.data()=" << str.data() << endl;
    // string::c_str() will guarrantee the chars ends with \0
    // both string::data() string::c_str() will return the origin character sequence.
    cout << "str.c_str()=" << str.c_str() << endl; 
    cout << "typeid(str.data()).name()=" << typeid(str.data()).name() << endl;

    cout << endl << "** string::at" << endl;
    str = "hello";
    cout << "str.at(1)=" << str.at(1) << endl;
    cout << "str[1]=" << str[1] << endl;

    // cout << endl << "** string::reserve" << endl;
    // str = "hello";
    // cout << "str=" << str << endl;
    // cout << "str.reserve()=" << str.reserve() << endl;

    cout << endl << "** string::swap" << endl;
    string str1 = "str1";
    string str2 = "str2";
    cout << "str1=" << str1 << ",str2=" << str2 << endl;
    str1.swap(str2);
    cout << "after swap, str1=" << str1 << ",str2=" << str2 << endl;
}

int main(int argc, char const *argv[])
{
    string str = "test";

    cout << "hello,world, string value is " << str << endl;
    
    TestIterator();
    TestFuncs();
    return 0;
}
