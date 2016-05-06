#include "..\Headers\Trans.h"

#include <algorithm>	


string Trans::trans_file_name = "";
vector<Trans_t> Trans::info_trans;

void Trans::startUp()
{
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

void Trans::addTrans()//adds a new transaction to the vector of transactions
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
void Trans::visAllTrans() const
{
	transHeader();
	for (Trans_t T : this->info_trans)
		visTrans(T);

	cout << endl << "========================================================" << endl;
}

void Trans::visClientTrans() const
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

void Trans::visDayTrans() const
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

void Trans::visBetweenDates() const
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

void Trans::transHeader() const
{
	cout << endl << "========================================================" << endl;
	cout << setw(NUM_BOX) << left << "Num :" << setw(DATE_BOX) << "Date :" << setw(PROD_BOX) << "Products :" << endl << endl;
}

void Trans::visDate(Date_t date) const {
	cout << setw(DATE_BOX) << left << to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
}

void Trans::visTrans(const Trans_t &T_t) const
{
	Visualize::instance()->visNumber(T_t.number); visDate(T_t.date); cout << Visualize::instance()->P_comma(T_t.products); cout << endl;
}

//====================================================================================
//================================== ADVERTISERS =====================================
//====================================================================================

Matrix Trans::createMatrix()
{//creates the matrix initialized with the true and false values, creates maps to associate position in matrix to information
	int position_matrix = 0;
	Matrix map_n_matrix;
	for (Trans_t transaction_line : this->info_trans) //iterates through the vector
	{
		for (string p_name : transaction_line.products) //p_name contains a product name
		{
			if (!map_n_matrix.product_to_i.count(p_name)) //meaning the product does not have an associated key
			{
				map_n_matrix.product_to_i[p_name] = position_matrix; //name to position
				map_n_matrix.i_to_product[position_matrix] = p_name; //position to name
				position_matrix++;
			}//if the product already existed it is ignored
		}
	}
	vector<bool> columns(position_matrix, false); 
	//creates column vector with size = to number of products brought by all users
	position_matrix = 0;
	for (Trans_t transaction_line : this->info_trans)
	{
		if (!map_n_matrix.c_number_to_i.count(transaction_line.number))
		{ //associates the client number to its position in the matrix
			map_n_matrix.c_number_to_i[transaction_line.number] = position_matrix;
			position_matrix++;
		}
	}
	map_n_matrix.prod_bought = vector< vector<bool> >(position_matrix, columns);
	//creates the matrix which will hold the true or false values

	for (Trans_t transaction_line : this->info_trans)
	{
		for (string p_name : transaction_line.products) //fills the matrix with the products bought
			map_n_matrix.prod_bought[map_n_matrix.c_number_to_i[transaction_line.number]][map_n_matrix.product_to_i[p_name]] = true;
	}

	return map_n_matrix; //matrix that already contains true and false values
}

void Trans::printRecommended(const vector<string> &P)
{//receives vector of string and prints it out
	cout << "The recommended products are : " << endl << "-->  ";
	for (string i : P)
		cout << i << "  ";
	cout << "<--";
}

void Trans::selectiveAd()
{
	cout << endl << "========================================================" << endl;
	Matrix product_list = createMatrix(); //holds matrix with true and false values already initialized
	vector<int> different_products; //vector which will hold the products the target client did not bought
	vector<int> temp_vec; //will temporarily hold the different products of the current user

	int
		client_number			 = Input_Asker::instance()->askClientName(), //client ID
		client_number_pos		 = product_list.c_number_to_i[client_number], //target client position in matrix
		n_columns				 = product_list.prod_bought[client_number_pos].size(),
		n_rows					 = product_list.prod_bought.size(), 
		cont                     = 0,
		max_number_of_equal_prod = 0;

	for (int client = 0; client < n_rows; client++)
	{
		if (client == client_number_pos)
			continue;
		for (int product = 0; product < n_columns; product++)
		{
			if (product_list.prod_bought[client_number_pos][product] && product_list.prod_bought[client][product])
				//if the inserted client bought the current product
				cont++;
			else if (product_list.prod_bought[client][product]) //if the current user bought the current product, but the target user didnt
				temp_vec.push_back(product);
		}
		// cont holds the amount of equal products the current user bought in relation to the target user
		if (cont < max_number_of_equal_prod)
		{ //clears the different product collected from current user
			temp_vec.clear();
			cont = 0;
		}
		else if (cont == max_number_of_equal_prod)
		{//merges the different products and the current vector which holds the different products
			mergeVectors(different_products, temp_vec);
			temp_vec.clear();
			cont = 0;
		}
		else
		{//replaces the old vector and clears the temp_vec
			max_number_of_equal_prod = cont;
			different_products = temp_vec;
			temp_vec.clear();
			cont = 0;
		}
	}//different_products holds repetitions of products bought which are different from the inputed user
	 //these repetitions are unsorted and the products are represented by its position in the matrix

	different_products = mostBought(different_products);
	//vector containing recommended products (represented by their position in the matrix)

	vector<string> recommended_product;
	for (int i : different_products)
		recommended_product.push_back(product_list.i_to_product[i]);
	//converts the product from its position in the matrix to its name(string) and then prints them out
	printRecommended(recommended_product);
}

vector<int> Trans::mostBought(vector<int> &p_bought)
//receives unsorted repetitions of different products and returns vector with products with more repetitions
{
	quicksort(p_bought);//orders the products
	int rep = 1, max_number = 0, vec_size = p_bought.size();
	vector<int> amount;
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

void Trans::mergeVectors(vector<int> &v1, vector<int> &v2)
{
	for (int i : v2)
		v1.push_back(i);
}

 //====================================================================================
 //================================= MISCELLANEOUS ====================================
 //====================================================================================

void Trans::update()
{
	ofstream fout;
	fout.open(temp_file_name);
	if (fout.is_open())
		for (Trans_t i : this->info_trans)																									//create function to return string of products to display
			fout << i.number << " ; " << to_string(i.date.day) + "/" + to_string(i.date.month) + "/" + to_string(i.date.year) << " ; " << Visualize::instance()->P_comma(i.products) << endl;
	fout.close();
	remove(this->trans_file_name.c_str());
	rename(temp_file_name.c_str(), this->trans_file_name.c_str());
}

string Trans::askProduct() const
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

vector<Trans_t> Trans::getInfo() const
{
	return info_trans;
}