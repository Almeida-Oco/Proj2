#include "..\Headers\Input_Asker.h"
#include "..\Headers\Supermarket.h"
#include "..\Headers\Trans.h"
#include "..\Headers\Client.h"

using namespace std;
//====================================================================================
//==================================== CLIENTS =======================================
//====================================================================================

int Supermarket::Input_Asker::T_askName() const
{
	set<Client_t>::iterator it;
	string client_name;
	cout << endl << "========================================================" << endl;
	cout << "Insert client name, CTRL+Z to go back " << endl;
	getline(cin, client_name);
	if (cin.fail())
	{
		if(!cin.eof())
			cin.ignore(999, '\n');
		return -1;
	}

	it = Client::instance()->nameBinarySearch(client_name);
	while (it->name != client_name)
	{
		cout << "Try again, CTRL+Z to go back " << endl;
		getline(cin, client_name);
		cin.ignore(999,'\n');
		if (cin.eof())
			return -1;
		else
			it = Client::instance()->nameBinarySearch(client_name);
	}

	return it->number;
}

string Supermarket::Input_Asker::askClientName(bool existing , set<Client_t>::iterator &it) const
{
	string client_name;
	cout << endl << "========================================================" << endl;
	cout << "Insert client name, CTRL+Z to go back " << endl;
	getline(cin, client_name);
	if (!cin.fail())
	{
		it = Client::instance()->nameBinarySearch(client_name);
		if (existing)
		{
			while (it == Client::instance()->getInfo().end() || it->name != client_name)
			{
				cout << "Try again, CTRL+Z to go back " << endl;
				getline(cin, client_name);
				if (cin.fail())
				{
					if (!cin.eof())
						cin.ignore(999, '\n');
					return "";
				}
				else
					it = Client::instance()->nameBinarySearch(client_name);
			}
		}
		else
		{

			while (!testText(client_name))
			{
				cout << "Try again, CTRL+Z to go back " << endl;
				getline(cin, client_name);
				if (cin.eof())
					return "";
				if (cin.fail())
					cin.clear();
				
				it = Client::instance()->nameBinarySearch(client_name);
				
			}
		}
	}
	else
	{
		if(!cin.fail())
			cin.ignore(999, '\n');
		cin.clear();
		return "";
	}

	return client_name;
}

bool Supermarket::Input_Asker::testNum(unsigned int num) const
{
	for (Client_t i : Client::instance()->getInfo())
	{
		if (i.number == num)
			return true;
	}
	return false;
}

//====================================================================================
//==================================== DATE =========================================
//====================================================================================

Date_t Supermarket::Input_Asker::askDate(int question , set<Trans_t>::iterator &it) const
{
	vector<string> date_numbers;
	Date_t input_date;
	string line;
	do
	{
		if (question == 0)
			cout << "Insert Lower bound (DD/MM/YY), CTRL+Z to go back " << endl;
		else if (question == 1)
			cout << "Insert Upper bound (DD/MM/YY), CTRL+Z to go back " << endl;
		else if (question == 2)
			cout << "Insert Day (DD/MM/YY), CTRL+Z to go back " << endl;
		getline(cin, line);
		if (!cin.fail())
		{
			cin.ignore(999, '\n');
			date_numbers = string_split(line, "/");
			for (unsigned int i = 0; i < date_numbers.size(); i++)
				date_numbers.at(i) = trim(date_numbers.at(i));

			if (date_numbers.size() == 3)
			{
				input_date.day = stoi(date_numbers.at(0));
				input_date.month = stoi(date_numbers.at(1));
				input_date.year = stoi(date_numbers.at(2));

				it = Trans::instance()->dateBinarySearch(input_date);
				if (it == Trans::instance()->getInfo().end())
					continue;
			}

		}
		else if (cin.eof())
		{
			input_date.day = 0;
			input_date.month = 0;
			input_date.year = 0;
			return input_date;
		}
	} while (!testDate(input_date));
	return input_date;
}

bool Supermarket::Input_Asker::testDate(const Date_t &D) const //tests if the string contains only number, bars '/'  and spaces
{
	if (D.year >= 1)
		if (D.month >= 1 && D.month <= 12)
			if (D.day >= 1 && D.day <= n_days(D.month, D.year))
				return true;
	return false;
}

unsigned int Supermarket::Input_Asker::n_days(const unsigned int M, const unsigned int Y) const
{
	if (M == JAN || M == MAR || M == MAY || M == JUL || M == AUG || M == OCT || M == DEC)
		return 31;
	else if (M == APR || M == JUN || M == SEP || M == NOV)
		return 30;
	else if (leapYear(Y))
		return 29;
	else
		return 28;
}

bool Supermarket::Input_Asker::leapYear(const unsigned int Y) const
{
	if (remainder(Y, 4) == 0 && remainder(Y, 100) != 0)
		return true;
	else if (remainder(Y, 400) == 0)
		return true;
	else
		return false;
}