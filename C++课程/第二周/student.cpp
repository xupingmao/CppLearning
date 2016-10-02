#include <iostream>
#include <cstdlib>
#include <cstring>
// #include <string>

using namespace std;

class Student
{
public:
    char name[100];
    int age;
    char studentNo[100];
    int avg1;
    int avg2;
    int avg3;
    int avg4;

    Student() {

    }
    ~Student() {

    }
    void ReadInput();
    void PrintAvgScore();
    
};

void Student::PrintAvgScore() {
    int avg = (avg1 + avg2 + avg3 + avg4) / 4;
    cout << name << "," << age << "," << studentNo << "," << avg << endl;
}

void Student::ReadInput() {
    // %s will read all the characters
    // scanf("%s,%d,%s,%d,%d,%d,%d", name,&age,studentNo,&avg1,&avg2,&avg3,&avg4);
    // cin >> name;
    // cin.ignore(1, ',');
    // cin >> age;
    // cin.ignore(1, ',');
    // cin >> studentNo;
    // cin.ignore(1, ',');
    // cin >> avg1;
    // cin.ignore(1, ',');
    // cin >> avg2;
    // cin.ignore(1, ',');
    // cin >> avg3;
    // cin.ignore(1, ',');
    // cin >> avg4;
    // cin.ignore(1, ',');

    char sentence[1024];
    cin >> sentence;
    
    char* pch = strtok(sentence, ",");
    int n = 0;
    while (pch != NULL) {
        ++n;
        switch (n) {
            case 1: strcpy(name, pch); break;
            case 2: age = atoi(pch); break;
            case 3: strcpy(studentNo, pch); break;
            case 4: avg1 = atoi(pch); break;
            case 5: avg2 = atoi(pch); break;
            case 6: avg3 = atoi(pch); break;
            case 7: avg4 = atoi(pch); break;
            default: break; // error
        }
        pch = strtok(NULL, ",");
    }


    // cout << "name=" << name << endl;
    // cout << "age=" << age << endl;
    // cout << "avg1=" << avg1 << endl;


}

int main(int argc, char const *argv[])
{
    Student s;
    s.ReadInput();
    s.PrintAvgScore();
    return 0;
}