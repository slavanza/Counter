#pragma once

// пока не используется
#define MAX_SIZE 256 // должно будет ограничивать размер переменной класса Real
#define MAX_INT_PART_SIZE 128 // для более тонкой настройки, чтобы было возможно выбрать,
#define MAX_FRAC_PART_SIZE 128 // какой объём памяти максимально возможен для каждой из частей числа


#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::ostream;

class Real
{
	bool sign;
	string Integer;
	string Fractional;
private:
	void checkNull();
	static string plus_Int(string, string);
	static string plus_Fract(string, string);
	static string minus_Int(string, string);
	static string minus_Fract(string, string);
	static int cmp(string, string);
public:
	Real();
	Real(int i);
	Real(string R);
	Real(const char* R);
	~Real();
	Real& operator=(const Real& R);
	Real& operator+=(const Real& R);
	Real(const Real& R);
	Real operator+(const Real& R);
	Real operator+(const int& i);
	Real operator-();
	Real operator-(const Real& R);
	Real operator*(const Real& R);
	Real operator/(const Real& R);
	bool operator==(const Real& R);
	bool operator==(const int& i);
	bool operator!=(const Real& R);
	bool operator!=(const int& i);
	friend bool operator<(const Real& R1, const Real& R2);
	friend bool operator<(const Real& R, const int& i);
	friend bool operator<(const int& i, const Real& R);
	friend bool operator>(const Real& R1, const Real& R2);
	friend bool operator>(const Real& R, const int& i);
	friend bool operator>(const int& i, const Real& R);
	friend ostream& operator<<(const ostream& o, const Real& r);
	friend Real operator+(const Real& r1, const Real& r2);
	// operator-
	friend Real operator*(const Real& R, const int& i);
	// operator/
};

Real operator+(const Real& r1, const Real& r2);
Real operator*(const Real& R, const int& i);