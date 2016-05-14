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
#include <vector>

class Supermarket::Trans
{
private:
	static std::string trans_file_name;
	static std::vector<Trans_t> info_trans;

public:
	static Trans *T_ptr;

	Trans() {};
	Trans(const Trans &T) {};

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
	std::vector<Trans_t> &getInfo() const;
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
	std::string askProduct() const;
	void visTrans(const Trans_t &T_t) const;
	void visDate(Date_t date) const;

};

#endif //!TRANS_H
