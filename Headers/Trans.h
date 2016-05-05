
#ifndef TRANS_H
#define TRANS_H

#include "..\Headers\Visualize.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Client.h"
#include <algorithm>
#include <string>
#include <vector>

void quicksort(vector<int> &qs);
vector<string> string_split(const string &line, const string spliter);
string remove_middle_spaces(const string &S);
string trim(string &str);

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
	void mergeVectors(vector<int> &v1, vector<int> &v2);
	vector<int> mostBought(vector<int> &p_bought);
	//receives vector, sorts it with quicksort and then returns vector which hold which number(s) had more repetitions

	void update();
private:
	string askProduct(Product &P);
	void visDate(Date_t date);
};

#endif // !TRANS_H