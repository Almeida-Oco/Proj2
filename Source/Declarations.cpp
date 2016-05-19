#include "..\Headers\Declarations.h"

using namespace std;

bool Date_t::operator> (const Date_t &D1) const
{
	if (this->year > D1.year)
		return true;
	else if (this->year == D1.year)
	{
		if (this->month > D1.month)
			return true;
		else if (this->day > D1.day)
			return true;
		else
			return false;
	}
	return false;
}
bool Date_t::operator>= (const Date_t &D1) const
{
	if (this->year > D1.year)
		return true;
	else if (this->year == D1.year)
	{
		if (this->month > D1.month)
			return true;
		else if (this->day >= D1.day)
			return true;
		else
			return false;
	}
	return false;
}
bool Date_t::operator<= (const Date_t &D1) const
{
	return !(*this > D1);
}
bool Date_t::operator< (const Date_t &D1) const
{ return !(*this >= D1); }
bool Date_t::operator== (const Date_t &D1) const
{
	return (this->day == D1.day && this->month == D1.month && this->year == D1.year);
}

bool Trans_t::operator< (const Trans_t &T1) const
{
	return this->date < T1.date;
}
bool Trans_t::operator<= (const Trans_t &T1) const
{
	return !(this->date > T1.date);
}
bool Trans_t::operator> (const Trans_t &T1) const 
{
	return (this->date > T1.date);
}

bool Client_t::operator< (const Client_t &C1) const
{
	return this->name < C1.name;
}
bool Client_t::operator<= (const Client_t &C1) const
{
	return this->name <= C1.name;
}
bool Client_t::operator> (const Client_t &C1) const
{
	return this->name > C1.name;
}