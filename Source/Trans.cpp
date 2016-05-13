#include "..\Headers\Trans.h"
#include "..\Headers\Supermarket.h"
#include "..\Headers\Product.h"
#include "..\Headers\Visualize.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Client.h"
#include "..\Headers\Bottom_10.h"

string Supermarket::Trans::trans_file_name = "";
vector<Trans_t> Supermarket::Trans::info_trans;

void Supermarket::Trans::startUp()
{
	unsigned int vector_size = 0;
	bool failed = false;
	vector<string> tokens;
	Trans_t transaction;
	string line;
	ifstream fin;
	do {
		failed = false;
		cout << "Insert the transactions file name" << endl;
		getline(cin, this->trans_file_name);
		fin.open(this->trans_file_name);
		while (!fin.is_open())
		{
			cout << "Unknown name. Please try again" << endl;
			getline(cin, this->trans_file_name);
			fin.open(this->trans_file_name);
		}

		if (cin >> vector_size)
			info_trans.reserve(vector_size);
		else
			continue;

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
			this->info_trans.push_back(transaction);
		}
		fin.close();
	} while (failed); //it if is the transaction files it copies its contents to a vector of structs

	sort(this->info_trans.begin(), this->info_trans.end());
}

//====================================================================================
//=================================== MODIFIERS ======================================
//====================================================================================

void Supermarket::Trans::addTrans()//adds a new transaction to the vector of transactions
{
	Trans_t T;
	T.number = Input_Asker::instance()->ask_c_number();
	T.date = Input_Asker::instance()->askDate(2);
	vector <string> prod_bought;
	string prod;
	do
	{
		prod = askProduct();
		prod_bought.push_back(prod);
		Client::instance()->addMoney(T.number, Product::instance()->getPrice(prod));
	} while (prod != "");
	T.products = prod_bought;
	this->info_trans.push_back(T);
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
	bool first = true;
	do
	{
		c_number = Input_Asker::instance()->askClientName();
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
		cout << endl << "========================================================" << endl;
	} while (c_number == -1);
}

void Supermarket::Trans::visDayTrans() const
{
	Date_t D;
	bool found = false, first = true;
	unsigned int i = 0;
	D = Input_Asker::instance()->askDate(2);

	for (Trans_t T : this->info_trans)
	{
		if (T.date.day == D.day && T.date.month == D.month && T.date.year == D.year)
		{
			if (first)
				transHeader();
			first = false;
			Visualize::instance()->visNumber(T.number); visDate(T.date); cout << Visualize::instance()->P_comma(T.products); cout << endl;
			found = true;
		}
		i++;
	}
	if (!found)
		cout << "The date is not on records" << endl;
	cout << endl << "========================================================" << endl;
}

void Supermarket::Trans::visBetweenDates() const
{
	bool first = true;
	Date_t lower_date = Input_Asker::instance()->askDate(0);
	Date_t upper_date = Input_Asker::instance()->askDate(1);

	for (Trans_t T : this->info_trans)
	{
		if (T.date > lower_date && T.date < upper_date)
		{
			if (first)
				transHeader();
			first = false;
			visTrans(T);
		}
	}
	cout << endl << "========================================================" << endl;
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


//FUNCAO QUE DA O ELEMENTO QUE APARECE MAIS VEZES NOS CLIENTES PARECIDOS COM O CLIENTE ALVO E O CLIENTE ALVO AINDA NAO TEM //
string Supermarket::Trans::maximu(vector<string>v)
{
	unsigned int u = 0, i = 0, max = 0, counter = 0, max_pos = 0;
	string product_wanted;

	while (u < Product::instance()->getSize())
	{

		while (i < v.size())            //this function gives me the name of the product that appears most times in a vector
		{
			if (Product::instance()->getProd(u) == v[i])
				counter++;
			i++;
		}
		if (counter > max)
		{
			max_pos = u;
			max = counter;
		}

		i = 0;
		counter = 0;
		u++;
	}


	return Product::instance()->getProd(max_pos);
}


int Supermarket::Trans::searchID_transactions(unsigned int p)
{
	int i = 0;

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


// usar para vetor so com id e produtos     Bottom_10::instance()->getCtoT();


//FUNC11 É AQUELA QUE FAZ A PUBLICIDADE EM SI,É ELA QUE CONSTROI A MATRIZ E QUE VERIFICA QUAIS OS CLIENTES PARECIDOS COM O CLIENTE ALVO
//E QUAL OS PRODUTOS DESTES QUE O ALVO AINDA NAO TEM ///

void Supermarket::Trans::Func11()
{
	Bottom_10::instance()->CtoT_init();
	vector< vector<bool> > publi(Bottom_10::instance()->getCtoT().size(), vector<bool>(Product::instance()->getSize()));

	vector<bool> vec_bool;


	int i = 0, p = 0, u = 0;
	

	bool verifi = false; //its a verifier that proves if the product in the list of products was bought by the client or not


	while (p < Bottom_10::instance()->getCtoT().size())
	{


		while (u<Product::instance()->getSize())
		{

			while (i < Bottom_10::instance()->getCtoT()[p].second.size())
			{
				if (Product::instance()->getProd(u) == Bottom_10::instance()->getCtoT()[p].second[i])
				{
					vec_bool.push_back(true);
					verifi = true;
					break;
				}

				i++;
			}

			if (verifi == false)
			{
				vec_bool.push_back(false);
			}
			verifi = false;
			u++;
			i = 0;


		}

		u = 0;
		publi[p] = vec_bool;
		vec_bool.clear();
		p++;

	}

	int max = -1, compare = 0;
	int id, line = 0, column = 0;
	int same_products = 0;
	vector <bool> vec_client_wanted;
	vector <string> vec_different_prod, vec_different_prod_aux;
	string product_wanted;


	cout << "ID: ";
	cin >> id;

	int position = searchID_transactions(id);

	while (position == -1)
	{
		cout << "Wrong ID, try again" << endl;
		Func11();
	}

	vec_client_wanted = publi[position];

	while (line < publi.size())
	{

		while (column < Product::instance()->getSize())
		{

			if (publi[line][column] && vec_client_wanted[column])
				compare++;                                             // In here I can see how many products does each line have in common with the client I chose and put in a vector of string the products that the client doesn't has
			else
			{

				if ((publi[line][column] == true) && (vec_client_wanted[column] == false))
				{
					vec_different_prod_aux.push_back(Product::instance()->getProd(column));
					same_products = 1;
				}

			}

			column++;

		}
		// same_products helps to prevent that 2 clients with exactly the same transactions are used in this program, because we will choose a product from a client that is similar to the one we chosen but with at least one different product in his/her transaction
		if ((compare < max) || (line == position) || (same_products == 0))
			vec_different_prod_aux.clear();
		else
		{
			if (compare > max)
			{
				vec_different_prod.clear();
				vec_different_prod = vec_different_prod_aux;
				vec_different_prod_aux.clear();
				max = compare;
			}
			else
			{
				vec_different_prod.insert(vec_different_prod.end(), vec_different_prod_aux.begin(), vec_different_prod_aux.end());
				vec_different_prod_aux.clear();
			}
		}
		compare = 0;
		column = 0;
		same_products = 0;
		line++;

	}


	cout << "The client " << id << " should be advertised with this product: " << maximu(vec_different_prod) << endl;

}




//====================================================================================
 //================================= MISCELLANEOUS ====================================
 //====================================================================================

void Supermarket::Trans::update()
{
	ofstream fout;
	fout.open(temp_file_name);
	if (fout.is_open())
		fout << info_trans.size();
		for (Trans_t i : this->info_trans)																									//create function to return string of products to display
			fout << i.number << " ; " << to_string(i.date.day) + "/" + to_string(i.date.month) + "/" + to_string(i.date.year) << " ; " << Visualize::instance()->P_comma(i.products) << endl;
	fout.close();
	remove(this->trans_file_name.c_str());
	rename(temp_file_name.c_str(), this->trans_file_name.c_str());
}

string Supermarket::Trans::askProduct() const
{
	int n_prod;
	map<int,string> num_prod = Visualize::instance()->visAllProd();
	do {
		cin >> n_prod;
		cin.ignore(9999, '\n');
		if (cin.fail() && !cin.eof())
		{
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Invalid input, try again" << endl;
			cout << "---> ";
			continue;
		}
		return (!cin.eof()) ? num_prod.at(n_prod) : "";
	} while (true);
}

vector<Trans_t> &Supermarket::Trans::getInfo() const
{
	return info_trans;
}
