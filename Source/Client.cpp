#include "..\Headers\Client.h"
#include "..\Headers\Trans.h"
#include "..\Headers\Visualize.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Bottom_10.h"
#include "..\Headers\Supermarket.h"

using namespace std;

//====================================================================================
//=================================== MODIFIERS ======================================
//====================================================================================

void Supermarket::Client::startUp()
{
	Bottom_10::instance()->CtoT_init();
	auto it = Bottom_10::instance()->getCtoT().begin();
	this->max_client_number = 0;
	vector<string> tokens;
	bool failed = false;
	do
	{
		failed = false;
		Client_t client;
		string line;
		ifstream fin;
		cout << "========================================================" << endl;
		cout << "Insert the clients file name" << endl;
		getline(cin, this->client_file_name);
		fin.open(this->client_file_name);
		if (!fin.is_open())
		{
			cout << "File not found" << endl;
			exit(0);
			break;
		}
		if (!(fin >> number_lines_cli))
		{
			fin.ignore(999, '\n');
			fin.clear();
			failed = true;
		}fin.ignore(999, '\n');
		

		while (getline(fin, line) && !failed)
		{
			tokens = string_split(line, " ; ");
			if (tokens.size() != 3)
			{
				failed = true;
				break;
			}
			if (!isdigit(tokens.at(2).at(0)))
			{
				failed = true;
				break;
			}

			client.name = trim(tokens.at(1));
			client.number = stoi(tokens.at(0));
			it = Bottom_10::instance()->searchSet(client.number);
			client.money = (  it == Bottom_10::instance()->getCtoT().end()  ) ?  0.0  :  Bottom_10::instance()->calcMoney(it->second);

			if (client.number > this->max_client_number)
				this->max_client_number = client.number;

			info_clients.insert(client);
		}

		if (failed)
		{
			cout << "Not the clients file, please try again" << endl;
			this->info_clients.clear();
		}

		fin.close();
	} while (failed); 
	
	unsigned int max_trans_number = Trans::instance()->getBiggestID();
	max_client_number = (max_trans_number > max_client_number) ? max_trans_number+1 : max_client_number+1;
} 

void Supermarket::Client::removeClient()
{//removes a certain client by removing it from the vector of clients
	set<Client_t>::iterator it;
	bool removed = false;
	unsigned int sz = info_clients.size(), i = 0;
	string c_name;
	c_name = Input_Asker::instance()->askClientName(true , it); //if user inputs CTRL+Z function returns ""
	
	if(c_name != "")
	{
		info_clients.erase(it);
		this->number_lines_cli--;   
	}
} 

void Supermarket::Client::addClient()//asks the client info, checks its validity and if it checks pushes back to the client vector
{
	Client_t new_c;
	string info, c_name;
	set<Client_t>::iterator it;
	c_name = Input_Asker::instance()->askClientName(false , it);

	if (c_name == "")
		return;

	new_c.number = this->max_client_number;
	this->max_client_number++;
	new_c.name = c_name;
	new_c.money = 0;
	info_clients.insert(it , new_c);
	this->number_lines_cli++;
}

void Supermarket::Client::addMoney(const string &S, const double amount)
{
	Client_t temp;
	set<Client_t>::iterator it = nameBinarySearch(S), temp_it;
	temp = *it;
	temp.money += amount;
	info_clients.erase(it);
	info_clients.insert(temp);
}

//====================================================================================
//================================== VISUALIZERS =====================================
//====================================================================================

void Supermarket::Client::visClient()
{
	bool found = false;
	set<Client_t>::iterator it;
	string client_name;
	do
	{
		cout << endl << "========================================================" << endl;
		cout << "Insert client name, CTRL+Z to go back " << endl;
		getline(cin, client_name);
		cin.ignore(999,'\n');
		if (!cin.eof())
			it = nameBinarySearch(client_name);
		else
			return;

		if (it->name == client_name)
		{
			found = true;
			clientHeader();
			Visualize::instance()->visNumber(it->number); Visualize::instance()->visName(it->name); visMoney(it->money);
			cout << endl;
		}
		if (!found)
			cout << "Try again, CTRL+Z to go back " << endl;
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
}

void Supermarket::Client::clientHeader()
{
	cout << endl << "========================================================" << endl;
	cout << setw(NUM_BOX) << left << "Num :" << setw(NAME_BOX) << "Name :" << setw(MONEY_BOX) << "Money :" << endl << endl;
}

void Supermarket::Client::visMoney(double money) {
	cout << setw(MONEY_BOX) << fixed << setprecision(2) << left << money;
}

//====================================================================================
//================================= MISCELLANEOUS ====================================
//====================================================================================

void Supermarket::Client::update()
{
	ofstream fout;

	fout.open(temp_file_name);
	if (fout.is_open())
		fout << this->number_lines_cli << endl;    
		for (Client_t i : info_clients)
			fout << i.number << " ; " << i.name << " ; " << i.money << endl;
	fout.close();
	remove(this->client_file_name.c_str());
	rename(temp_file_name.c_str(), this->client_file_name.c_str());
}

string Supermarket::Client::NumtoName(unsigned int num) const
{
	for (auto it = info_clients.begin(); it != info_clients.end(); it++)
	{
		if (it->number == num)
			return it->name;
	}
	return "";
}

set<Client_t>::iterator Supermarket::Client::nameBinarySearch(const string &element)
{
	set<Client_t>::iterator it;
	it = info_clients.begin();
	for (it; it != info_clients.end(); it++)
	{
		if (it->name == element)
			return it;
	}
	return it;
}

set<Client_t> &Supermarket::Client::getInfo()
{
	return info_clients;
}
