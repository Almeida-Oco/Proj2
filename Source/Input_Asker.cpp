#include "..\Headers\Input_Asker.h"

string trim(string &str);
vector<string> string_split(const string &line, const string spliter);

//====================================================================================
//==================================== CLIENTS =======================================
//====================================================================================

int Input_Asker::ask_c_number(const Client &C)
{
	int c_number;
	do
	{
		cout << "Insert client number" << endl;
		cin >> c_number;
		cin.ignore(9999, '\n');
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Insert client number" << endl;
			cin >> c_number;
		}
	} while (!testNum(c_number , C));

		return c_number;
}

int Input_Asker::askClientName(const vector<Client_t> &info_c)
{
	bool found = false;
	string client_name;
	do
	{
		cout << "Insert client name : " << endl;
		getline(cin, client_name);
		for (Client_t client_line : info_c)
		{
			if (client_line.name == client_name)
			{
				found = true;
				return client_line.number;
			}
		}
		if (!found)
			cout << "Client not found, please try again" << endl;
	} while (!found);
	return -1;
}

bool Input_Asker::testNum(unsigned int num, const Client &C)
{
	for (Client_t i : C.getInfo())
	{
		if (i.number == num)
			return true;
	}
	return false;
}

//====================================================================================
//==================================== DATE =========================================
//====================================================================================

Date_t Input_Asker::askDate(int question)
{
	int cont = 0, date_placeholder = 0;
	vector<string> date_numbers;
	Date_t input_date;
	string line;
	do
	{
		if (question == 0)
			cout << "Please insert the lower bound : (DD/MM/YY) " << endl;
		else if (question == 1)
			cout << "Please insert the upper bound : (DD/MM/YY)" << endl;
		else if (question == 2)
			cout << "Please insert the desired day : (DD/MM/YY)" << endl;
		getline(cin, line);

		date_numbers = string_split(line, "/");
		for (unsigned int i = 0; i < date_numbers.size(); i++)
			date_numbers.at(i) = trim(date_numbers.at(i));
		if (date_numbers.size() == 3 && testDate(date_numbers.at(0)) && testDate(date_numbers.at(1)) && testDate(date_numbers.at(2)))
		{
			input_date.day = stoi(date_numbers.at(0));
			input_date.month = stoi(date_numbers.at(1));
			input_date.year = stoi(date_numbers.at(2));
			break;
		}
	} while (true);

	return input_date;
}

bool Input_Asker::testDate(const string &date) //tests if the string contains only number, bars '/'  and spaces
{
	bool found = false; //only here to check if the string given is not null
	for (char i:date)
	{
		if (!(i >= ZERO && i <= NINE))
			return false;
		found = true;
	}
	if (!found)
		return false;
	else
	return true;
}