#include <vector>
#include <iostream>

using namespace std;

// methods
// insert(v.begin() + position, value);
// void push_back(value);
// void pop_back(value);

void printVector(vector<int> &v) {
    cout << "intVector = [";
    for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i)
    {
        cout << *i << ",";
    }
    cout << "]" << endl << endl;
}

void test_push_back(vector<int> &v, int num) 
{
    v.push_back(num);
    cout << "push_back(" << num << ");" << endl;
    printVector(v);
}

void test_insert(vector<int> &v, int pos, int value) {
    v.insert(v.begin() + pos, value);
    cout << "insert(" << pos << "," << value << ")" << endl;
    printVector(v);
}

void test_erase(vector<int> &v, int start, int end) {
    // erase [start, end-1];
    v.erase(v.begin() + start, v.begin() + end);
    cout << "erase(" << start << "," << end << ")" << endl;
    printVector(v);
}

void test_erase(vector<int> &v, int pos) {
    v.erase(v.begin() + pos);
    cout << "erase(" << pos << ");" << endl;
    printVector(v);
}

void test_pop_back(vector<int> &v) {
    v.pop_back();
    cout << "pop_back()" << endl;
    printVector(v);
}

int main(int argc, char const *argv[])
{
    vector<int> intVector;

    test_push_back(intVector, 1);
    test_push_back(intVector, 2);

    test_insert(intVector, 1, 10);
    test_insert(intVector, 2, 4);

    // segment fault , insert method is not save
    // test_insert(intVector, 100, 10); 

    test_erase(intVector, 1, 2);
    test_erase(intVector, 1);

    test_pop_back(intVector);

    // add some elements
    test_insert(intVector, 3);
    test_insert(intVector, 100);

    return 0;
}