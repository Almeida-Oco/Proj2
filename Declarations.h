#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <map>
#include <vector>
#include <string>

using namespace std;

//CONSTANTS
const string temp_file_name = "lqpebcsgs285nmgs99n2exzgguwcajf.txt";
const unsigned int SPACE = 32;
const unsigned int P_V = 59;
const unsigned int DOT = 46;
const unsigned int ZERO = 48;
const unsigned int NINE = 57;
const unsigned int COMMA = 44;
const unsigned int BAR = 47;
const unsigned int NEW_LINE = 10;
const unsigned int A = 65;
const unsigned int Z = 90;
const unsigned int a = 97;
const unsigned int z = 122;
const unsigned int NUM_BOX = 8;
const unsigned int NAME_BOX = 25;
const unsigned int MONEY_BOX = 10;
const unsigned int DATE_BOX = 15;
const unsigned int PROD_BOX = 20;

//STRUCTS
struct Matrix {
	vector < vector <bool> > prod_bought; //matrix
	map<string, int> product_to_i; //map that relates the poduct name to its position in the matrix
	map<int, int> c_number_to_i; //returns the position of the client in the matrix
	map<int, string> i_to_product; //map that given a position in the matrix returns the corresponding product
};

struct Client_t {
	unsigned int number;
	string name;
	double money;
};

struct Date_t {
	unsigned int day;
	unsigned int month;
	unsigned int year;
};

struct Trans_t
{
	unsigned int number;
	Date_t date;
	vector<string> products;
};

#endif // !DECLARATIONS_H
