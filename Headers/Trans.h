#ifndef TRANS_H
#define TRANS_H

#include "..\Headers\Visualize.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Client.h"
#include <algorithm>
#include <string>
#include <vector>

class Client;
class Product;
using namespace std;


class Trans {
	static string trans_file_name;
	static vector<Trans_t> info_trans;

	static Trans *T_pt;
public:
	Trans() {};
	Trans(const Trans &T) {};

	//MODIFIERS
	void startUp();
	void addTrans();
	void update();

	//VISUALIZERS
	void transHeader() const;
	void visClientTrans() const;
	void visAllTrans() const;
	void visDayTrans() const;
	void visBetweenDates() const;

	//ADVERTISEMENT
	Matrix createMatrix();
	void printRecommended(const vector<string> &P);
	void selectiveAd(); 
	void mergeVectors(vector<int> &v1, vector<int> &v2);
	vector<int> mostBought(vector<int> &p_bought);
	
	//MISC
	vector<Trans_t> getInfo() const;
	static Trans *instance()
	{
		if (!T_pt)
			T_pt = new Trans;
		return T_pt;
	}
private:
	string askProduct() const;
	void visTrans(const Trans_t &T_t) const;
	void visDate(Date_t date) const;
};

#endif // !TRANS_H