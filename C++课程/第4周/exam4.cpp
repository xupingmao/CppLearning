#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

string Add(string& value1, string&value2);
string Sub(string& value1, string&value2);
string Mul(string& value1, string& value2);
string Div(string& value1, string& value2);
int Compare(string& value1, string& value2);

// <array> can do the job
template<typename T>
class Array {
	private:
		T* values;
		int size;
		
	public:
		Array(int size) {
			this->size = size;
			this->values = new T[size];
			// initialize values to be 0. 
			for (int i = 0; i < size; i++) {
				values[i] = 0;
			}
		}
		
		~Array () {
			delete [] values;
		}
		
		T& operator[](int index) {
			return values[index];
		}
		
		string to_string() {
			string result;
		    for (int i = size-1; i >= 0; --i) {
		    	// skip 0 at first
		    	if (values[i] == 0 && result.length() == 0) {
		    		continue;
				}
				result += values[i] + '0';
			}
			return result;
		}
};

class BigInteger {
	private:
		string value;
		 
	public:
		BigInteger(string value) {
			this->value = value;
		}
		
		BigInteger& operator+ (BigInteger& v) {
			this->value = Add(value, v.value);
			return *this;
		}
		
		BigInteger& operator- (BigInteger& v) {
			this->value = Sub(value, v.value);
			return *this;
		}
		
};

class Expr {
public:
    string value1;
    string op; // +,-,*,/ operator
    string value2;

    void Read();
    string Calc();
};

void Expr::Read() {
    cin >> value1 >> op >> value2;
}

string Expr::Calc() {
    if (op == "+") {
        return Add(value1, value2);
    } else if (op == "-") {
        // return Sub();
        return Sub(value1, value2); 
    } else if (op == "*") {
        return Mul(value1, value2);
    } else if (op == "/") {
        // return Div();
        return Div(value1, value2);
    }
    return NULL;
}

int Compare(string& value1, string& value2) {
	// value1.length > 0 and value2.length > 0
	if (value1[0] != '-') {
		if (value2[0] == '-') {
			return 1;
		} else {
			if (value1.length() > value2.length()) {
				return 1;
			} else if (value1.length() < value2.length()) {
				return -1;
			} else {
				return strcmp(value1.c_str(), value2.c_str());
			}
		}
	} else {
		if (value2[0] != '-') {
			// value1 is negative, value2 is positive.
			return -1;
		} else {
			if (value1.length() > value2.length()) {
				return -1;
			} else if (value1.length() < value2.length()) {
				return 1;
			} else {
				return strcmp(value2.c_str(), value1.c_str());
			}
		}
	}
}

string Add(string& value1, string& value2) {
    int p1 = value1.length() - 1;
    int p2 = value2.length() - 1;

	int maxsize = max(p1+1,p2+1);
	Array<int> values(maxsize+1);

    for (int i = 0; p1 >= 0 || p2 >= 0; --p1, --p2, ++i) {
    	int c1 = 0, c2 = 0;
		if (p1 >= 0) {
			c1 = value1[p1] - '0';
		}
    	if (p2 >= 0) {
    		c2 = value2[p2] - '0';
		}
    	int v = c1 + c2;
    	// cout << "c1=" << c1 << ",c2=" << c2 << endl;
    	values[i] += v;
    	if (values[i] >= 10) {
    		values[i] -= 10;
    		values[i+1] += 1;
		}
	}
	return values.to_string();
}

string Sub(string& value1, string& value2) {
	int n = Compare(value1, value2);
	if (n == 0) {
		return "0";
	} else if (n < 0) {
		return "-" + Sub(value2, value1);
	}
	int p1 = value1.length() - 1;
	int p2 = value2.length() - 1;
	
	int maxsize = max(p1+1,p2+1);
	Array<int> values (maxsize);
	
	for (int i = 0; p1 >= 0 || p2 >= 0; --p1, --p2, ++i) {
    	int c1 = 0, c2 = 0;
		if (p1 >= 0) {
			c1 = value1[p1] - '0';
		}
    	if (p2 >= 0) {
    		c2 = value2[p2] - '0';
		}
    	int v = c1 - c2;
    	// cout << "c1=" << c1 << ",c2=" << c2 << ",values[i]=" << values[i] << endl;
		values[i] += v;
		if (values[i] < 0) {
			values[i] += 10;
			values[i+1] -= 1;
		}
	}
	return values.to_string();
}

string SimpleMul(string& value1, int c) {
	int maxsize = value1.length() + 1;
	Array<int> values(maxsize);
	for (int i = 0, p = value1.length() - 1; p >= 0; --p, ++i) {
		int c1 = value1[p] - '0';
		int v = c1 * c;
		values[i] += v;
		// cout << "c1=" << c1 << ",c=" << c << endl;
		if (values[i] >= 10) {
			div_t div_result = div(values[i], 10);
			values[i+1] += div_result.quot;
			values[i] = div_result.rem;
		}
	}
	return values.to_string();
}

void LeftShift(string& value, int step) {
	while (--step >= 0) {
		value += "0";
	}
}

string Mul(string& value1, string& value2) {
	string result = "0";
	for(int i = value1.length() - 1; i >= 0; --i) {
		int c = value1[i] - '0';
		string temp_result = SimpleMul(value2, c);
		LeftShift(temp_result, value1.length() - i - 1); // left shift by decimal
		// cout << "result=" << result << ", temp_result=" << temp_result << endl;
		result = Add(result, temp_result);
	}
	return result;
}

int GuessQuotient(string& left, string& right) {
	int guess = 0;
	
	while (guess < 9) {
		string part = SimpleMul(right, guess+1);
		if (Compare(part, left) > 0) {
			break;
		}
		guess++;
	}
	return guess;
}

string Div(string& value1, string& value2) {
	int n = Compare(value1, value2);
	if (n < 0) {
		return "0";
	} else if (n == 0) {
		return "1";
	}
	int gap = value1.length() - value2.length();
	
	string result;
	string rest = value1;
	string factor = value2;
	LeftShift(factor, gap);
	
	while (gap >= 0 && Compare(rest, value2) >= 0) {
		int guess = GuessQuotient(rest, factor);
		// cout << "rest=" << rest << ", factor=" << factor << ",guess=" << guess << endl;
		
		string part = SimpleMul(factor, guess);
		rest = Sub(rest, part);
		
		-- gap;

		// adjust divition factor
		factor = value2;
		LeftShift(factor, gap);
		
		// skip first 0
		if (result.length() == 0 && guess == 0) {
			continue;
		}
		result += guess + '0';
	}
	
	if (gap >=0 && result.length() != 0) {
		LeftShift(result, gap+1);
	}
	
	return result;
}

int main(int argc, char const *argv[])
{
    Expr expr;
    expr.Read();
    string value = expr.Calc();
    cout << value << endl;
    return 0;
}
