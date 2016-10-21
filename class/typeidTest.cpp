#include <iostream>
#include <typeinfo>

using namespace std;


class Base {
public:
  virtual void Print() = 0;
};

class Child: public Base {
public:
  virtual void Print();
};

void Child::Print() {
  cout << "hello" << endl;
}


int main()
{
  Base * p = new Child();
  cout << typeid(p).name() << endl;
  delete p;
  Child* c = new Child();
  cout << typeid(c).name() << endl;
  c->Print();
  delete c;
  
  decltype(10) t1 = 10;
  auto t2 = 1.0;
  
  cout << typeid(t1).name() << endl;
  cout << typeid(t2).name() << endl;
  
  return 0;
}
