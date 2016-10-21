#include <iostream>
#include <typeinfo>

using namespace std;

typedef struct person_t {
	string name;
	int age;
} Person;

Person Lexp()
{
	Person p = {"Jhon", 10};
	cout << "Left" << endl;
	return p;
}

string Rexp()
{
	cout << "Right" << endl;
	return "hello";
}

int main()
{
  Lexp().name = Rexp();
  
  return 0;
}
