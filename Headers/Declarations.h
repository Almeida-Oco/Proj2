#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <map>
#include <vector>
#include <string>
#include <map>

//CONSTANTS
const std::string temp_file_name = "lqpebcsgs285nmgs99n2exzgguwcajf.txt";

const unsigned int SPACE = 32;
const unsigned int ZERO = 48;
const unsigned int NINE = 57;
const unsigned int A = 65;
const unsigned int Z = 90;
const unsigned int a = 97;
const unsigned int z = 122;
const unsigned int NUM_BOX = 8;
const unsigned int NAME_BOX = 25;
const unsigned int MONEY_BOX = 10;
const unsigned int DATE_BOX = 15;
const unsigned int PROD_BOX = 20;
const unsigned int JAN = 1;
const unsigned int FEB = 2;
const unsigned int MAR = 3;
const unsigned int APR = 4;
const unsigned int MAY = 5;
const unsigned int JUN = 6;
const unsigned int JUL = 7;
const unsigned int AUG = 8;
const unsigned int SEP = 9;
const unsigned int OCT = 10;
const unsigned int NOV = 11;
const unsigned int DEC = 12;


//STRUCTS
struct Client_t {
	unsigned int number;
	std::string name;
	double money;

	bool operator< (const Client_t &C1) const;
	bool operator<= (const Client_t &C1) const;
	bool operator> (const Client_t &C1) const;
};

struct Date_t {
	unsigned int day;
	unsigned int month;
	unsigned int year;

	bool operator> (const Date_t &D1) const;
	bool operator>= (const Date_t &D1) const;
	bool operator< (const Date_t &D1) const;
};

struct Trans_t
{
	unsigned int number;
	Date_t date;
	std::vector<std::string> products;

	bool operator< (const Trans_t &T1) const;
	bool operator<= (const Trans_t &T1) const;
	bool operator> (const Trans_t &T1) const;
};

std::vector<std::string> string_split(const std::string &line, const std::string &spliter);
std::string remove_middle_spaces(const std::string &S);
std::string trim(std::string &str);
bool testText(const std::string &c_name);

#endif // !DECLARATIONS_H
