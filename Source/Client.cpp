#include "..\Headers\Client.h"


string Client::client_file_name = "";
unsigned int Client::max_client_number = 0;
vector<Client_t> Client::info_clients;
//====================================================================================
//=================================== MODIFIERS ======================================
//====================================================================================

Client::Client()
{
	this->max_client_number = 0;
	unsigned int temp;
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
		{
			info_clients.clear();
			continue;
		}
		fin.close();
	} while (failed); //and not the products, if it is the client file, it copies the information to a vector of Structs
	this->max_client_number++;
} 

void Client::removeClient()
{//removes a certain client by removing it from the vector of clients

	bool removed = false;
	unsigned int c_number, sz = info_clients.size(), i = 0;
	Input_Asker Ask;
	do
	{
		c_number = Ask.askClientName(info_clients);
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

void Client::addClient()//asks the client info, checks its validity and if it checks pushes back to the client vector
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
	info_clients.push_back(new_c);
}

void Client::addMoney(const unsigned int c_num, const double amount)
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

void Client::visClient()
{
	bool found = false;
	Visualize V;
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
				V.visNumber(i.number); V.visName(i.name); visMoney(i.money);
				cout << endl;
				break;
			}
		}
		cout << endl << "========================================================" << endl;
		if (!found)
			cout << "Client not found, please try again : " << endl;
	} while (!found);
}

void Client::visAllClients()
{
	Visualize V;
	clientHeader();
	for (Client_t i : info_clients)
	{
		V.visNumber(i.number); V.visName(i.name); visMoney(i.money);
		cout << endl;
	}
	cout << endl << "========================================================" << endl;
}

void Client::clientHeader()
{
	cout << endl << "========================================================" << endl;
	cout << setw(NUM_BOX) << left << "Num :" << setw(NAME_BOX) << "Name :" << setw(MONEY_BOX) << "Money :" << endl << endl;
}

//====================================================================================
//================================= MISCELLANEOUS ====================================
//====================================================================================

int Client::findName(const string &c_name) //searches the client vector for a given name, and returns its position on the vector
{//if the name exists, if not then return -1
	int sz = info_clients.size();
	for (int i = 0; i<sz; i++)
	{
		if (info_clients.at(i).name == c_name)
			return i;
	}
	return -1;
}

void Client::visMoney(double money) {
	cout << setw(MONEY_BOX) << fixed << setprecision(2) << left << money;
}

void Client::update()
{
	ofstream fout;

	fout.open(temp_file_name);
	if (fout.is_open())
		for (Client_t i : info_clients)
			fout << i.number << " ; " << i.name << " ; " << i.money << endl;
	fout.close();
	remove(this->client_file_name.c_str());
	rename(temp_file_name.c_str(), this->client_file_name.c_str());
}
