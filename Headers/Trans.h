#ifndef TRANS_H
#define TRANS_H
#include "Supermarket.h"
#include "Declarations.h"
#include <algorithm>	
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <set>

class Supermarket::Trans
{
private:
	std::string trans_file_name;
	std::multiset<Trans_t> info_trans;
	static Trans *T_ptr;
	unsigned int number_lines_trans; 

	//used to avoid multiple class objects
	Trans() {};
	Trans(const Trans &T) {};
public:
	

	//MODIFIERS
	void startUp();
	void addTrans();
	void update();

	//VISUALIZERS
	void visClientTrans() const;
	void visAllTrans() const;
	void visDayTrans() const;
	void visBetweenDates() const;

	//ADVERTISEMENT
	void selectiveAd();

	//MISC
	std::multiset<Trans_t> &getInfo();
	std::set<Trans_t>::iterator dateBinarySearch(const Date_t &element) const;
	unsigned int getBiggestID() const;
	static Trans *instance()
	{
		if (!T_ptr)
			T_ptr = new Trans;
		return T_ptr;
	}
private:
	void transHeader() const;
	std::vector<std::string> mostBought(std::vector<std::string> &p_bought);
	int	searchID_transactions(unsigned int p);
	std::vector<std::string> askProduct(bool B) const;
	void visTrans(const Trans_t &T_t) const;
	void visDate(Date_t date) const;

};

#endif //!TRANS_H
