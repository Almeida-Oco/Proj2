#include "..\Headers\Product.h"
#include "..\Headers\Supermarket.h"

using namespace std;

void Supermarket::Product::startUp()
{
	bool failed = false;
	string line;
	vector<string> tokens;
	// int test;
	ifstream fin;
	do
	{
		failed = false;
		cout << "========================================================" << endl;
		cout << "Insert the products file name" << endl;
		getline(cin, this->product_file_name);
		fin.open(this->product_file_name);
		if (!fin.is_open())
		{
			cout << "File not found" << endl;
			exit(0);
			break;
		}
		fin.ignore(999, '\n');
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

void Supermarket::Product::update()
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

double Supermarket::Product::getPrice(const string &product)
{
	auto it = this->prod_price.find(product);
	if (it != this->prod_price.end())
		return it->second;
	return -1;
}

double Supermarket::Product::getPrice(const vector<string> &product)
{
	double final = 0;
	for (string S : product)
		final += prod_price.at(S);
	return final;
}

string Supermarket::Product::getProd(unsigned int position)
{
	unsigned int cont = 0;
	for (pair<string, double> it : prod_price)
	{
		if (cont == position)
			return it.first;
		cont++;
	}
	return "";
}

unsigned int Supermarket::Product::getSize()
{
	return prod_price.size();
}