#include "..\Headers\Trans.h"
#include "..\Headers\Supermarket.h"
#include "..\Headers\Product.h"
#include "..\Headers\Visualize.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Client.h"
#include "..\Headers\Bottom_10.h"

using namespace std;

void Supermarket::Trans::startUp()
{

	bool failed = false;
	vector<string> tokens;
	Trans_t transaction;
	string line;
	ifstream fin;
	do {
		failed = false;
		cout << "========================================================" << endl;
		cout << "Insert the transactions file name" << endl;
		getline(cin, this->trans_file_name);
		fin.open(this->trans_file_name);
		while (!fin.is_open())
		{
			cout << "File not found" << endl;
			exit(0);
			break;
		}
		if (!(fin >> number_lines_trans))
		{
			failed = true;
			cin.clear();
			cin.ignore(999, '\n');
			continue;
		}
		fin.ignore(999, '\n');
		fin.clear();

		while (getline(fin, line))
		{//fazer um get do numero , data e produtos;
			tokens = string_split(line, " ; ");
			if (tokens.size() != 3)
			{
				failed = true;
				break;
			}
			if (isalpha(tokens.at(2).at(0)))
			{
				transaction.products = string_split(tokens.at(2), ",");
				for (unsigned int i = 0; i<transaction.products.size(); i++)
					transaction.products.at(i) = trim(transaction.products.at(i));
			}
			else
			{
				failed = true;
				break;
			}
			vector<string> date_tokens = string_split(tokens.at(1), "/");
			transaction.date.day = stoi(date_tokens.at(0));
			transaction.date.month = stoi(date_tokens.at(1));
			transaction.date.year = stoi(date_tokens.at(2));
			transaction.number = stoi(tokens.at(0));
			info_trans.insert(transaction);
		}
		if (failed)
		{
			cout << "Not the transactions file, please try again" << endl;
			this->info_trans.clear();
		}

		fin.close();
	} while (failed); //it if is the transaction files it copies its contents to a vector of structs
}

/*====================================================================================**
**=================================== MODIFIERS ======================================**
**====================================================================================*/

void Supermarket::Trans::addTrans()//adds a new transaction to the vector of transactions
{
	Trans_t T;
	set<Trans_t>::iterator it;
	int c_number = Input_Asker::instance()->T_askName();
	vector <string> prod_bought;
	string prod;

	if (c_number != -1)
		T.number = c_number;
	else
		return;

	T.date = Input_Asker::instance()->askDate(2 , it);
	if(T.date.day != 0)
		prod_bought = askProduct( true );
	if (prod_bought.size() != 0)
	{
		Client::instance()->addMoney(Client::instance()->NumtoName(T.number), Product::instance()->getPrice(prod_bought));
		T.products = prod_bought;
		info_trans.insert(it, T);
		this->number_lines_trans++;
	}
}

//====================================================================================
//================================== VISUALIZERS =====================================
//====================================================================================

void Supermarket::Trans::visAllTrans() const
{
	transHeader();
	for (Trans_t T : this->info_trans)
		visTrans(T);

	cout << endl << "========================================================" << endl;
}

void Supermarket::Trans::visClientTrans() const
{
	unsigned int c_number;
	string name;
	set<Client_t>::iterator it;
	bool first = true;
	do
	{
		name = Input_Asker::instance()->askClientName(true,it);
		if (name != "" && it != Client::instance()->getInfo().end())
			c_number = it->number;
		else  //if user inserted CTRL+Z
			break;
		for (Trans_t T : this->info_trans)
		{
			if (T.number == c_number)
			{
				if (first) 
					transHeader();
				first = false;
				visTrans(T);
			}
		}
		break;

	} while (true);
}

void Supermarket::Trans::visDayTrans() const
{
	Date_t D;
	set<Trans_t>::iterator it;
	bool found = false, first = true;
	unsigned int i = 0;
	D = Input_Asker::instance()->askDate(2,it);
	if (D.day == 0)
		return;
	for (it ; it != Trans::instance()->getInfo().end() ; it++)
	{
		
		if (it->date == D)
		{
			found = true;
			if (first && found)
			{
				transHeader();
				first = false;
			}
			visTrans(*it);
		}
			
		else
			break;
	}


	if (!found)
		cout << endl << "The date is not on records " << endl;
}

void Supermarket::Trans::visBetweenDates() const
{
	bool first = true, found = false;
	set<Trans_t>::iterator temp_it;
	Date_t lower_date = Input_Asker::instance()->askDate(0,temp_it);
	Date_t upper_date = Input_Asker::instance()->askDate(1, temp_it);
	if (lower_date.day == 0 || upper_date.day == 0)
		return;

	for (temp_it = info_trans.begin(); temp_it != info_trans.end(); temp_it++)
	{
		if (temp_it->date >= lower_date && temp_it->date <= upper_date)
		{
			found = true;
			if (first)
			{
				transHeader();
				first = false;
			}
			visTrans(*temp_it);
			
		}
		else if (temp_it->date > upper_date)
			break;
	}

	if (!found)
		cout << endl << "No transaction inbetween" << endl;
}

void Supermarket::Trans::transHeader() const
{
	cout << endl << "========================================================" << endl;
	cout << setw(NUM_BOX) << left << "Num :" << setw(DATE_BOX) << "Date :" << setw(PROD_BOX) << "Products :" << endl << endl;
}

void Supermarket::Trans::visDate(Date_t date) const {
	cout << setw(DATE_BOX) << left << to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
}

void Supermarket::Trans::visTrans(const Trans_t &T_t) const
{
	Visualize::instance()->visNumber(T_t.number); visDate(T_t.date); cout << Visualize::instance()->P_comma(T_t.products); cout << endl;
}

//====================================================================================
//================================== ADVERTISERS =====================================
//====================================================================================

vector<string> Supermarket::Trans::mostBought(vector<string> &p_bought)
//receives unsorted repetitions of different products and returns vector with products with more repetitions
{
	sort(p_bought.begin(), p_bought.end());
	int rep = 1, max_number = 0, vec_size = p_bought.size();
	vector<string> amount;
	for (int i = 0; i<vec_size; i++)
	{
		if (i == p_bought.size() - 2)
		{
			if (p_bought.at(i) == p_bought.at(i + 1))
				rep++;
			else
			{
				if (rep > max_number)
				{
					max_number = rep;
					amount.clear();
					amount.push_back(p_bought.at(i));
					rep = 1;
				}
				if (rep == max_number)
				{
					amount.push_back(p_bought.at(i));
					rep = 1;
				}
				i++;
			}
		}

		if (rep > max_number)
		{
			max_number = rep;
			amount.clear();
			amount.push_back(p_bought.at(i));
		}
		else if (rep == max_number)
		{
			amount.push_back(p_bought.at(i));
		}
		if (i == vec_size - 1)
			break;
		else if (p_bought.at(i) != p_bought.at(i + 1))
			rep = 1;
		else
			rep++;

	}
	return amount;
}//return vector with the most bought products by the most similar clients

int Supermarket::Trans::searchID_transactions(unsigned int p)
{
	unsigned int i = 0;

	while (i<Bottom_10::instance()->getCtoT().size())
	{
		if (Bottom_10::instance()->getCtoT()[i].first == p)         //with this function, I can know the line I should access in the bidimensional vector that I create in Func11.
		{
			return i;
		}
		else
			i++;
	}

	return -1;
}

void Supermarket::Trans::selectiveAd() 
{
	Bottom_10::instance()->CtoT_init();
	int c_number = Input_Asker::instance()->T_askName();
	if (c_number == -1)
		return;
	unsigned int target_position = searchID_transactions(c_number);
	vector<string> alreadyAccountedFor;
	bool verifi = false;
	vector< vector<bool> > publi(Bottom_10::instance()->getCtoT().size(), vector<bool>(Product::instance()->getSize()));
	vector<bool> vec_bool;

	for (unsigned int trans_prods = 0; trans_prods < Bottom_10::instance()->getCtoT().size(); trans_prods++ , vec_bool.clear()) 
	{//iterates through CtoT, a set that contains a single transaction for each client
		for (unsigned int prods_i=0; prods_i < Product::instance()->getSize(); prods_i++) 
		{//iterates the product map
			for (unsigned int i=0; i < Bottom_10::instance()->getCtoT().at(trans_prods).second.size(); i++) 
			{//iterates products client bought
				if (Product::instance()->getProd(prods_i) == (Bottom_10::instance()->getCtoT().at(trans_prods)).second.at(i))
				{
					vec_bool.push_back(true);
					verifi = true;
					break;
				}
			}

			if (!verifi)
				vec_bool.push_back(false);

			verifi = false;
		}

		publi.at(trans_prods) = vec_bool;
	}

	int max = -1, compare = 0;
	vector <string> vec_different_prod, vec_different_prod_aux;
	string product_wanted;

	for (unsigned int line = 0; line < publi.size(); line++ , compare = 0)
	{
		if (line == target_position)
			continue;
		for (unsigned int column = 0; column < Product::instance()->getSize(); column++)
		{
			if (publi[line][column] && publi[target_position][column])
				compare++;

			else if (publi[line][column] && !publi[target_position][column])
				vec_different_prod_aux.push_back(Product::instance()->getProd(column));

		}


		if (compare < max && vec_different_prod_aux.size() != 0)
			vec_different_prod_aux.clear();
		else if (vec_different_prod_aux.size() != 0 && compare > max)
		{
			vec_different_prod.clear();
			vec_different_prod = vec_different_prod_aux;
			vec_different_prod_aux.clear();
			max = compare;
		}
		else if (vec_different_prod_aux.size() != 0)
		{
			vec_different_prod.insert(vec_different_prod.end(), vec_different_prod_aux.begin(), vec_different_prod_aux.end());
			vec_different_prod_aux.clear();
		}
	}

	Visualize::instance()->printRecommended(mostBought(vec_different_prod));
}

//====================================================================================
 //================================= MISCELLANEOUS ====================================
 //====================================================================================

std::set<Trans_t>::iterator Supermarket::Trans::dateBinarySearch(const Date_t &element) const
{
	set<Trans_t>::iterator it;
	it = info_trans.begin();
	for (it; it != info_trans.end(); it++)
	{
		if (it->date == element)
			return it;
	}
	return it;
}

unsigned int Supermarket::Trans::getBiggestID() const
{
	unsigned int max = 0;
	for (Trans_t T : info_trans)
	{
		if (T.number > max)
			max = T.number;
	}
	return max;
}

void Supermarket::Trans::update()
{
	ofstream fout;
	fout.open(temp_file_name);
	if (fout.is_open())
	fout << this->number_lines_trans << endl;
		for (Trans_t i : this->info_trans)																									//create function to return string of products to display
			fout << i.number << " ; " << to_string(i.date.day) + "/" + to_string(i.date.month) + "/" + to_string(i.date.year) << " ; " << Visualize::instance()->P_comma(i.products) << endl;
	fout.close();
	remove(this->trans_file_name.c_str());
	rename(temp_file_name.c_str(), this->trans_file_name.c_str());
}

vector<string> Supermarket::Trans::askProduct(bool first_time) const
{
	int n_prod;
	bool found = false;
	vector<string> prod_bought;
	map<int, string> num_prod = Visualize::instance()->visAllProd(first_time);
	auto it = num_prod.begin();
	do {
		found = false;
		cin >> n_prod;
		cin.ignore(9999, '\n');
		for (it = num_prod.begin(); it != num_prod.end(); it++)
		{
			if (it->first == n_prod)
			{
				found = true;
				break;
			}
		}

		if ((cin.fail() || !found) && !cin.eof())
		{
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Invalid input, try again" << endl;
			cout << "---> ";
			continue;
		}
		else if (cin.eof())
			break;
		prod_bought.push_back(it->second);
		cout << "---> ";

	} while (!cin.eof());
	return prod_bought;
}

multiset<Trans_t> &Supermarket::Trans::getInfo()
{
	return info_trans;
}

unsigned int Supermarket::Trans::getNum()
{
	return this->number_lines_trans;
}