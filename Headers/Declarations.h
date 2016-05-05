#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <map>
#include <vector>
#include <string>
#include <map>

using namespace std;

//EXperimentar github

//CONSTANTS
const string temp_file_name = "lqpebcsgs285nmgs99n2exzgguwcajf.txt";

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

	bool operator< (const Client_t &C1);
};

struct Date_t {
	unsigned int day;
	unsigned int month;
	unsigned int year;

	bool operator> (const Date_t &D1);
	bool operator< (const Date_t &D1);
};

struct Trans_t
{
	unsigned int number;
	Date_t date;
	vector<string> products;

	bool operator< (const Trans_t &T1);
};

#endif // !DECLARATIONS_H
