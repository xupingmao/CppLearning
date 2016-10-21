#include<iostream>
#include<cstring>

using namespace std;

class Person {

  private:
  char name[100];
  int age = 0;  

  public:
   
  Person() {
    strcpy(this->name, "emptry");
    this->age = 0;
	cout << __func__ << "::Person()"	<< endl;
  } 
  Person(const char* name) {
    strcpy(this->name, name);
    // this->name = name;
	cout << __func__ << "::Person(const char*)" << endl;
  }

  Person(const char* name, int age) {
    strcpy(this->name, name);
    // this->name = name;
    this->age = age;
	cout << __func__ << "::Person(const char*,int)" << endl;
  }

  // 复制构造函数
  /*
  Person(Person& p) {
    strcpy(this->name, p.name);
    this->age = age;
  }
  */

  // 赋值构造函数
  Person &operator=(int age) {
    strcpy(this->name, "copy");
    this->age = age;
    return *this;
  }

  void introduce() {
    cout << "hello, my name is " << this->name << ", and I am " << age << " years old" << endl;
  }

};

class Child :public Person {

	
public:
	Child()
	{
		cout << __func__ << "::Child()" << endl;
	}
	
	Child(int age)
	{
		cout << __func__ << "::Child(int)" << endl;
		age = 10;
	}
};


int main() {
  Child c; // 无参构造函数
  Person p = "test";// 转换构造函数
  p.introduce();
  Person p2("hello", 20); // 普通构造函数 
  p2.introduce();
  Person p3 = {"p3", 10}; // C++11 构造函数
  p3.introduce();
  Person p4;
  p4 = 10; // 赋值构造函数
  p4.introduce();
  // Person p5 = p4; // 复制构造函数
  // p5.introduce();
  
  Child c2(10);
  
  return 0;
}

