#include "Real.h"

enum { POS = true, NEG = false };


string IntToStr(const int& i)
{
	string result;
	int _i = i;
	while (_i)
	{
		result += (char)(_i % 10 + 48);
		_i /= 10;
	}
	char buf;
	int len = result.size();
	for (int i = 0; i < len / 2; i++)
	{
		buf = result[i];
		result[i] = result[len - 1 - i];
		result[len - 1 - i] = buf;
	}
	return result;
}


void Real::checkNull()
{
	while ((Integer[0] == '0') && (Integer.size() > 1))
		Integer.erase(0, 1);
	while ((Fractional[Fractional.size() - 1] == '0') && (Fractional.size() > 1))
		Fractional.erase(Fractional.size(), 1);
}


string Real::plus_Int(string s1, string s2)
{
	string result = s1.size() > s2.size() ? s1 : s2;
	string sum = s1.size() > s2.size() ? s2 : s1;
	int off = 0;
	for (int i = 0; i < sum.size(); i++)
	{
		int dec = (int)((char)result[result.size() -1 - i]) - 48 + (int)((char)sum[sum.size() -1 - i] - 48) + off;
		if (dec > 9)
		{
			off = dec / 10;
			dec %= 10;
		}
		else
			off = 0;
		result[result.size() - 1 - i] = (char)(dec + 48);
	}
	if (off)
	{
		string add;
		add += (char)(off + 48);
		result = add + result;
	}
	checkNull();
	return result;
}

string Real::plus_Fract(string s1, string s2)
{
	string result = s1.size() > s2.size() ? s1 : s2;
	string sum = s1.size() > s2.size() ? s2 : s1;
	int off = 0;
	for (int i = 0; i < sum.size(); i++)
	{
		int dec = (int)(result[result.size() - i] - 48) + (int)(sum[sum.size() - i] - 48) + off;
		if (dec > 9)
		{
			off = dec / 10;
			dec %= 10;
		}
		else
			off = 0;
		result[result.size() - i] = (char)(dec + 48);
	}
	if (s1.size() > s2.size())
	{
		if (result.size() > s1.size())
		{
			result.erase(0, 1);
			throw 1;
		}
	}
	else
	{
		if (result.size() > s2.size())
		{
			result.erase(0, 1);
			throw 1;
		}
	}
	checkNull();
	return result;
}


int Real::cmp(string s1, string s2)
{
	if (s1 == s2)
		return 0;
	int i = 0;
	int len = s1.size() - s2.size();
	if(len > 0)
		while (i < s1.size() && i < s2.size())
		{
			if (s1[i + len] > s2[i])
				return -1;
			if (s1[i + len] < s2[i])
				return 1;
		}
	else
		while (i < s1.size() && i < s2.size())
		{
			if (s1[i] > s2[i + len])
				return -1;
			if (s1[i] < s2[i + len])
				return 1;
		}
	return 0;
}


Real::Real()
{
	sign = POS;
	Integer = Fractional = "0";
}


Real::Real(int i)
{
	sign = i > 0 ? true : false;
	Integer = IntToStr(i);
	Fractional = "0";
}


Real::Real(string R):Real()
{
	int startpos = R.find("-") + 1;
	if (startpos)
		sign = NEG;
	int pos = R.find(".");
	if (pos == -1)
		pos = R.size();
	else
		Fractional.erase();
	for (int i = startpos; i < pos; i++)
	{
		Integer += R[i];
	}
	for (int i = pos + 1; i < R.size(); i++)
	{
		Fractional += R[i];
	}
	checkNull();
}


Real::Real(const char* R):Real(string(R))
{
	
}


Real::~Real()
{
}

Real& Real::operator=(const Real& R)
{
	Integer = R.Integer;
	Fractional = R.Fractional;
	return *this;
}

Real::Real(const Real& R)
{
	*this = R;
}


Real Real::operator+(const Real& R)
{
	Real result = R;
	int code = 0;
	// + and +
	// - and -
	if (((*this > 0) && (R > 0)) || ((*this < 0) && (R < 0)))
	{
		try
		{
			result.Fractional = plus_Fract(Fractional, R.Fractional);
		}
		catch (int i)
		{
			string add;
			add += (char)(i + 48);
			result.Integer = plus_Int(Integer, add);
		}
		result.Integer = plus_Int(Integer, R.Integer);
	}
	// + and -
	return result;
}


Real Real::operator+(const int& i)
{
	return *this + Real(i);
}


/*Real Real::operator-(const Real& R)
{
	
}*/


bool Real::operator==(const Real& R)
{
	this->checkNull();
	((Real)R).checkNull();
	if (Integer == R.Integer && Fractional == R.Fractional)
		return true;
	return false;
}


bool Real::operator==(const int& i)
{
	return *this == Real(i);
}


bool Real::operator!=(const Real& R)
{
	return !(*this == R);
}


bool Real::operator!=(const int& i)
{
	return !(*this == Real(i));
}


bool operator<(const Real& R1, const Real& R2)
{
	if (R1.sign < R2.sign)
		return true;
	if (R1.sign > R2.sign)
		return false;
	int I = ((Real)R1).cmp(R1.Integer, R2.Integer);
	if (I < 0)
		return true;
	int r = ((Real)R1).cmp(R1.Fractional, R2.Fractional);
	if (r < 0)
		return true;
	return false;
}


bool operator<(const Real& R, const int& i)
{
	return R < Real(i);
}


bool operator<(const int& i, const Real& R)
{
	return Real(i) < R;
}


bool operator>(const Real& R1, const Real& R2)
{
	if (R1.sign > R2.sign)
		return true;
	if (R1.sign < R2.sign)
		return false;
	int I = ((Real)R1).cmp(R1.Integer, R2.Integer);
	if (I > 0)
		return true;
	int r = ((Real)R1).cmp(R1.Fractional, R2.Fractional);
	if (r > 0)
		return true;
	return false;
}


bool operator>(const Real& R, const int& i)
{
	return R > Real(i);
}


bool operator>(const int& i, const Real& R)
{
	return Real(i) > R;
}


ostream& operator<<(const ostream& o, const Real& r)
{
	(ostream&)o << r.Integer << "." << r.Fractional;
	return (ostream&)o;
}


/*Real operator+(const Real& r1, const Real& r2)
{
	Real result = r1;
	int code = 0;
	// + and +
	if ((r1 > 0) && (r2 > 0))
	{
		try
		{
			result.Fractional = ((Real)r1).plus_Fract(r1.Fractional, r2.Fractional);
		}
		catch (int i)
		{
			string add;
			add += (char)(i + 48);
			result.Integer = ((Real)r1).plus_Int(result.Integer, add);
		}
		result.Integer = ((Real)r1).plus_Int(result.Integer, r2.Integer);
	}

	//
	return result;
}*/