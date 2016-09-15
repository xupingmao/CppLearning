#include <iostream>
#include <cstring>

using namespace std;

class Animal {

  public:
  void virtual Print() = 0;
};


class Dog:public Animal {
    public:
    char type[20];

    Dog(const char* type) {
        strcpy(this->type, type);
    }
    void virtual Print();
};

void Dog::Print() {
    cout << "hello,I am a " << type << endl;
}

class Cat:public Animal {
    public:
    char type[20];
    
    Cat(const char* type) {
        strcpy(this->type, type);
    }
    void virtual Print();
};

void Cat::Print() {
    cout << "hello, cat here" << endl;
}


int main() {
    Animal *a;

    a = new Dog("dog");

    a->Print();
    delete a;
    a = new Cat("cat");
    a->Print();
    delete a;
    return 0;

}
