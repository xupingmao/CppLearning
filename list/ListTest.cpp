#include <iostream>
#include <list>

using namespace std;


void PrintList(list<int> &nList)
{
    cout << '[';
    for (list<int>::iterator it=nList.begin(); it != nList.end(); ++it) {
        cout << *it << ",";
    }
    cout << ']' << endl;
}

int main(int argc, char const *argv[])
{
    list<int> nList;

    nList.push_back(1);
    nList.push_back(2);
    nList.push_back(3);
    nList.push_back(4);

    PrintList(nList);

    nList.pop_back();
    cout << "pop_back: " << endl;
    PrintList(nList);

    nList.pop_front();
    cout << "pop_front: " << endl;

    PrintList(nList);

    return 0;
}

