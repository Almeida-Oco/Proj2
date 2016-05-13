#include <climits>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//FUNCTIONS AND ETC
#include "..\Headers\Supermarket.h"
#include "..\Headers\Declarations.h"
#include "..\Headers\Bottom_10.h"
#include "..\Headers\Product.h"
#include "..\Headers\Visualize.h"
#include "..\Headers\Client.h"
#include "..\Headers\Trans.h"
#include "..\Headers\Input_Asker.h"

Supermarket *Supermarket::S_pt;
Supermarket::Client *Supermarket::Client::C_ptr;
Supermarket::Product *Supermarket::Product::P_ptr;
Supermarket::Trans *Supermarket::Trans::T_ptr;
Supermarket::Input_Asker *Supermarket::Input_Asker::IA_ptr;
Supermarket::Visualize *Supermarket::Visualize::V_ptr;
Supermarket::Bottom_10 *Supermarket::Bottom_10::B10_ptr;



bool testText(const string &c_name);
void update_n_exit();
//last function to be called, updates the files, according to the current information on the info_(vectors)



int main()
{
	Supermarket();
	Supermarket::Bottom_10::instance()->Source();
	//MainMenu();
	//update_n_exit();
}




void update_n_exit()
{

	//Client::instance()->update();
	//Product::instance()->update();
	//Trans::instance()->update();
	cout << "GOODBYE" << endl;
	exit(0);
}










//====================================================================================
//===================================== STRING =======================================
//====================================================================================
vector<string> string_split(const string &line, const string spliter)
{
	unsigned int pos_spliter = 0, cont_spliter = 0, sz = line.size(), splt_sz = spliter.size(), inicio = 0;
	vector<string> split_string;

	for (unsigned int i = 0; i < sz; i++)
	{
		if (i == sz - 1)
		{
			pos_spliter = i + 1;
			split_string.push_back(line.substr(inicio, pos_spliter - inicio));
			break;
		}

		if (line.at(i) == spliter.at(cont_spliter))
		{
			if (cont_spliter != splt_sz)
				cont_spliter++;
			if (cont_spliter == splt_sz)
			{
				pos_spliter = i - (splt_sz-1);
				split_string.push_back(line.substr(inicio, pos_spliter - inicio));
				inicio = pos_spliter + 1;
				inicio = i + 1;
				cont_spliter = 0;
			}
		}
	}
	return split_string;
}

string remove_middle_spaces(const string &S)
{//receives trimmed string with only spaces in the middle, and returns a string that contains only 1 space between names
	string final_string;
	bool space = false;

	for (char c : S)
	{
		if (c != ' ')
		{
			final_string.push_back(c);
			space = true;
			continue;
		}
		else
		{
			if (space)
				final_string.push_back(' ');
			space = false;
		}
	}
	return final_string;
}

string trim(string &str)
{
	size_t first = -1;
	size_t last = -1;
	first = str.find_first_not_of(' ');
	last = str.find_last_not_of(' ');
	if (first != ULONG_MAX && last != ULONG_MAX)
		return remove_middle_spaces(str.substr(first, (last - first + 1)));
	else
		return "";
}

//====================================================================================
//=============================== MISCELLANEOUS ======================================
//====================================================================================

bool testText(const string &c_name) 
{
	for (char i : c_name)
	{
		if (!((i >= A && i <= Z) || (i >= a && i <= z) || i == SPACE))
			return false;
	}
	return true;
}