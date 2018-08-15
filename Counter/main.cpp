#include <iostream>

#include "Real.h"

using std::cout;
using std::endl;



int main(int argC, char** argV)
{
	Real r1("1.23");
	Real r2("2");
	cout << r1 << endl << r2 << endl;
	cout << (bool)(r1 > r2) << endl;
	cout << (bool)(r1 > 0) << endl;
	Real r = r1 + r2;
	cout << r;
	getchar();
}