#include "..\Headers\Product.h"

string Product::product_file_name = "";
map<string, double> Product::prod_price;

Product::Product()
{
	bool failed = false;
	string line;
	vector<string> tokens;
	// int test;
	ifstream fin;
	do
	{
		failed = false;
		cout << "Insert the products file name" << endl;
		getline(cin, this->product_file_name);
		fin.open(this->product_file_name);
		if (!fin.is_open())
		{
			cout << "File not found" << endl;
			exit(0);
			break;
		}

		while (getline(fin, line))
		{
			tokens = string_split(line, ";");
			if (tokens.size() != 2)
			{
				failed = true;
				cout << "Not the products file, please try again" << endl;
				this->prod_price.clear();
				break;
			}
			this->prod_price[remove_middle_spaces(trim(tokens.at(0)))] = stod(tokens.at(1));
		}
		fin.close();
	} while (failed); //if it is the products file, it copies the information to a vector of strings
}

void Product::update()
{
	ofstream fout;

	fout.open(temp_file_name);
	if (fout.is_open())
		for (const std::pair<string, double> i : prod_price)
			fout << i.first << " ; " << i.second << endl;
	fout.close();
	remove(this->product_file_name.c_str());
	rename(temp_file_name.c_str(), this->product_file_name.c_str());
}

double Product::getPrice(const string &product)
{
	auto it = this->prod_price.find(product);
	if (it != this->prod_price.end())
		return it->second;
	return -1;
}

string Product::getProd(double price)
{
	const double delta = 0.001; //erro aceitavel no preco
	for (auto P : this->prod_price)
	{
		if (P.second >= (price - delta) || P.second <= (price + delta))
			return P.first;
	}
	return "";
}