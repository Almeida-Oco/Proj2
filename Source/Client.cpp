#include "..\Headers\Client.h"
#include "..\Headers\Trans.h"
#include "..\Headers\Visualize.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Supermarket.h"

using namespace std;

string Supermarket::Client::client_file_name = "";
unsigned int Supermarket::Client::max_client_number = 0;
vector<Client_t> Supermarket::Client::info_clients;
//====================================================================================
//=================================== MODIFIERS ======================================
//====================================================================================

void Supermarket::Client::startUp()
{
	unsigned int vector_size = 0, temp = 0;
	this->max_client_number = 0;
	vector<string> tokens;
	bool failed = false;
	do
	{
		failed = false;
		Client_t client;
		string line;
		ifstream fin;
		cout << "Insert the clients file name" << endl;
		getline(cin, this->client_file_name);
		fin.open(this->client_file_name);
		while (!fin.is_open())
		{
			cout << "Unknown name. Please try again" << endl;
			getline(cin, this->client_file_name);
			fin.open(this->client_file_name);
		}

		if (cin >> vector_size)
			info_clients.reserve(vector_size);
		else
			continue;

		while (getline(fin, line))
		{
			tokens = string_split(line, " ; ");
			if (tokens.size() != 3)
			{
				failed = true;
				break;
			}
			if (isdigit(tokens.at(2).at(0)))
				client.money = stod(tokens.at(2));
			else
			{
				failed = true;
				break;
			}

			client.name = trim(tokens.at(1));
			client.number = stoi(tokens.at(0));

			temp = client.number;
			if (temp > this->max_client_number)
				this->max_client_number = temp;
			info_clients.push_back(client);
		}

		if (failed)
			info_clients.clear();

		fin.close();
	} while (failed); 

	sort(this->info_clients.begin(), this->info_clients.end());
	
	unsigned int max_trans_number = Trans::instance()->getBiggestID();
	max_client_number = (max_trans_number > max_client_number) ? max_trans_number : max_client_number;
} 

void Supermarket::Client::removeClient()
{//removes a certain client by removing it from the vector of clients

	bool removed = false;
	unsigned int c_number, sz = info_clients.size(), i = 0;
	do
	{
		c_number = Input_Asker::instance()->askClientName();
		for (i=0 ; i<sz ; i++)
		{
			if (c_number == info_clients.at(i).number)
			{
				removed = true;
				break;
			}
		}
		if (!removed)
			cout << "Client not found , please try again " << endl;
	} while (!removed);
	info_clients.erase(info_clients.begin() + i);
} 

void Supermarket::Client::addClient()//asks the client info, checks its validity and if it checks pushes back to the client vector
{
	Client_t new_c;
	string info, c_name;
	cout << endl << "-----------------------------------------------------" << endl;
	do {
		cout << "Insert client name" << endl;
		getline(cin, c_name);
	} while (!testText(c_name));
	new_c.number = this->max_client_number;
	this->max_client_number++;
	new_c.name = c_name;
	new_c.money = 0;
	info_clients.insert(findInsertPos(new_c), new_c);
}

void Supermarket::Client::addMoney(const unsigned int c_num, const double amount)
{
	unsigned int sz = info_clients.size();
	for (unsigned int i = 0; i < sz; i++)
	{
		if (info_clients.at(i).number == c_num)
			info_clients.at(i).money += amount;
	}
}

//====================================================================================
//================================== VISUALIZERS =====================================
//====================================================================================

void Supermarket::Client::visClient()
{
	bool found = false;
	string client_name;
	do
	{
		cout << "Insert client name : " << endl;
		getline(cin, client_name);
		if (!testText(client_name))
			continue;
		for (Client_t i : info_clients)
		{
			if (i.name == client_name)
			{
				found = true;
				clientHeader();
				Visualize::instance()->visNumber(i.number); Visualize::instance()->visName(i.name); visMoney(i.money);
				cout << endl;
				break;
			}
		}
		cout << endl << "========================================================" << endl;
		if (!found)
			cout << "Client not found, please try again : " << endl;
	} while (!found);
}

void Supermarket::Client::visAllClients()
{
	clientHeader();
	for (Client_t i : info_clients)
	{
		Visualize::instance()->visNumber(i.number); Visualize::instance()->visName(i.name); visMoney(i.money);
		cout << endl;
	}
	cout << endl << "========================================================" << endl;
}

void Supermarket::Client::clientHeader()
{
	cout << endl << "========================================================" << endl;
	cout << setw(NUM_BOX) << left << "Num :" << setw(NAME_BOX) << "Name :" << setw(MONEY_BOX) << "Money :" << endl << endl;
}

//====================================================================================
//================================= MISCELLANEOUS ====================================
//====================================================================================

vector<Client_t>::iterator Supermarket::Client::findInsertPos(const Client_t &C) const
{
	return info_clients.begin() + findPos(C, 0, info_clients.size() - 1) + 1;
}

unsigned int Supermarket::Client::findPos(const Client_t &C, unsigned int start, unsigned int end) const
{
	if (start != end)
	{
		if (C < info_clients.at((start + end) / 2))
			return findPos(C, start, ((start + end) / 2) - 1);
		else if (C > info_clients.at((start + end) / 2))
			return findPos(C, ((start + end) / 2) + 1, end);
		else
			return (start + end) / 2;
	}

	if (start == end && C > info_clients.at(start))
		return start + 1;
	if (start == end && C < info_clients.at(start) && start != 0)
		return start - 1;
	else
		return start; //only happens when the element should be inserted in the first position

}

int Supermarket::Client::findName(const string &c_name) //searches the client vector for a given name, and returns its position on the vector
{//if the name exists, if not then return -1
	int sz = info_clients.size();
	for (int i = 0; i<sz; i++)
	{
		if (info_clients.at(i).name == c_name)
			return i;
	}
	return -1;
}

void Supermarket::Client::visMoney(double money) {
	cout << setw(MONEY_BOX) << fixed << setprecision(2) << left << money;
}

void Supermarket::Client::update()
{
	ofstream fout;

	fout.open(temp_file_name);
	if (fout.is_open())
		fout << info_clients.size() << endl;
		for (Client_t i : info_clients)
			fout << i.number << " ; " << i.name << " ; " << i.money << endl;
	fout.close();
	remove(this->client_file_name.c_str());
	rename(temp_file_name.c_str(), this->client_file_name.c_str());
}

