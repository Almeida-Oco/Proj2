
#ifndef TRANS_H
#define TRANS_H

#include "..\Headers\Visualize.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Client.h"
#include <algorithm>
#include <string>
#include <vector>

void quicksort(vector<int> &qs); //function used to easily call qksort

vector<string> string_split(const string &line, const string spliter);
//similar to java string_split, given a string and a spliter, it returns the different parts of the original string in a vector

string remove_middle_spaces(const string &S);
//leaves only one middle space between the different words there might exist

string trim(string &str);
//removes all spaces at the left and at the right of the string

using namespace std;
class Trans {
	static string trans_file_name;
	static vector<Trans_t> info_trans;
	static vector<Client_t> info_clients;
public:
	Trans();

	//MODIFIERS
	void addTrans(Product &P, Client &C);

	//VISUALIZERS
	void transHeader();
	void visClientTrans(const Client &C);
	void visAllTrans();
	void visDayTrans();
	void visBetweenDates();

	//ADS
	Matrix createMatrix();
	void printRecommended(const vector<string> &P);
	void selectiveAd(const Client &C); 
	//main function for the advertisement
	void mergeVectors(vector<int> &v1, vector<int> &v2);
	vector<int> mostBought(vector<int> &p_bought);
	//receives vector, sorts it with quicksort and then returns vector which hold which number(s) had more repetitions

	void update();
private:
	bool cmpDates(const Date_t &date1, const Date_t &d2);
	bool cmpDates(const Trans_t &T1, const Trans_t &T2);
	void visDate(Date_t date);
};

#endif // !TRANS_H