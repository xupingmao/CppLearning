#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;
// 在此处补充你的代码
class MyString {
	
	private:
		int length;
		char* value;
	
	public:
		
		char* GetValue() {
			return value;
		}
		
		int GetLength() {
			return length;
		}
		
		MyString () {
			value = new char[1];
			value[0] = 0;
			length = 0;
		}
		
		MyString (char* value, int length);
		
		MyString (const char *value) {
			length = strlen(value);
			this->value = new char[length+1];
			strcpy(this->value, value);
			this->value[length] = 0;

			// cout << "constructor, (const char*) " << endl;
		}
		
		MyString (const MyString& str) {
			char* value = str.value;
			length = strlen(value);
			this->value = new char[length+1];
			strcpy(this->value, value);
			this->value[length] = 0;
			// cout << "constructor, (MyString&)" << endl;
		}
		
		~MyString () {
			if (length != 0) {
				delete[] value;
			} 
		}
		
		MyString operator+ (MyString& str); 
		MyString operator+ (const char* value);
		MyString& operator+=(const char* value);
		MyString& operator= (MyString str);
		MyString& operator= (const char* sz);
		MyString operator() (int start, int length);
		
		char& operator[](int index) {
			return value[index];
		}
		
		
		bool operator< (MyString& str) {
			return strcmp(this->value, str.value) < 0;
		}
		
		bool operator> (MyString& str) {
			return strcmp(this->value, str.value) > 0;
		}
		
		bool operator== (MyString& str) {
			return strcmp(this->value, str.value) == 0;
		}
};  

MyString:: MyString(char* value, int length) {
	this->length = length;
	this->value = new char[length+1];
	strcpy(this->value, value);
	this->value[length] = 0;
}

MyString MyString::operator+(MyString& str) {
	int size = length + str.length + 1;
	char* temp = new char[size];
	strcpy(temp, value);
	strcat(temp, str.value);
	MyString v(temp);
	delete[] temp;
	return v;
}

MyString MyString::operator+(const char* str) {
	int size = length + strlen(str) + 1;
	char* temp = new char[size];
	strcpy(temp, value);
	strcat(temp, str);
	MyString v(temp);
	delete[] temp;
	return v;
}

MyString& MyString::operator+=(const char* str) {
	int size = length + strlen(str) + 1;
	this->length = size - 1;
	char* old = this->value;
	
	this->value = new char[size];
	strcpy(this->value, old);
	strcat(this->value, str);
	
	delete [] old;
	return *this; 
}

MyString& MyString::operator=(MyString str){
	// cout << "operator= (MyString)" << endl;
	delete[] value;
	length = str.length;
	value = new char[length+1];
	strcpy(value, str.value);
	value[length] = 0;
	return *this;
}

MyString& MyString::operator=(const char* sz) {
	// cout << "operator= (const char*)" << endl;
	delete [] value;
	length = strlen(sz);
	value = new char[length+1];
	strcpy(value, sz);
	return *this;
}

MyString MyString::operator() (int start, int length) {
	MyString v (value+start, length);
	return v;
}

MyString operator+ (const char* str, MyString& value) {
	int size = value.GetLength() + strlen(str) + 1;
	char* temp = new char[size];
	strcpy(temp, str);
	strcat(temp, value.GetValue());
	MyString v(temp);
	delete[] temp;
	return v;
}

ostream& operator<< (ostream& out, MyString str) {
	return out << str.GetValue();
}

// END
int CompareString( const void * e1, const void * e2)
{
        MyString * s1 = (MyString * ) e1;
        MyString * s2 = (MyString * ) e2;
        if( * s1 < *s2 )
                 return -1;
        else if( *s1 == *s2)
                 return 0;
        else if( *s1 > *s2 )
                 return 1;
}
int main()
{
        MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
        MyString SArray[4] = {"big","me","about","take"};
        cout << "1. " << s1 << s2 << s3<< s4<< endl;
        s4 = s3;
        s3 = s1 + s3;
        cout << "2. " << s1 << endl;
        cout << "3. " << s2 << endl;
        cout << "4. " << s3 << endl;
        cout << "5. " << s4 << endl;
        cout << "6. " << s1[2] << endl;
        s2 = s1;
        s1 = "ijkl-";
        s1[2] = 'A' ;
        cout << "7. " << s2 << endl;
        cout << "8. " << s1 << endl;
        s1 += "mnop";
        cout << "9. " << s1 << endl;
        s4 = "qrst-" + s2;
        cout << "10. " << s4 << endl;
        s1 = s2 + s4 + " uvw " + "xyz";
        cout << "11. " << s1 << endl;
        qsort(SArray,4,sizeof(MyString),CompareString);
        for( int i = 0;i < 4;i ++ )
        cout << SArray[i] << endl;
        //s1的从下标0开始长度为4的子串
        cout << s1(0,4) << endl;
        //s1的从下标5开始长度为10的子串
        cout << s1(5,10) << endl;
        return 0;
}
