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
	unsigned int vector_size = 0;
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
		if (!fin.is_open())
		{
			cout << "File not found" << endl;
			exit(0);
			break;
		}

		if (fin >> vector_size)
			info_clients.reserve(vector_size);
		fin.ignore(999, '\n');
		fin.clear();

		while (getline(fin, line))
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
			client.money = (Bottom_10::instance()->searchSet(client.number) == Bottom_10::instance()->getCtoT().end() ) ? 0.0 : Bottom_10::instance()->calcMoney(Bottom_10::instance()->searchSet(client.number)->second);

			if (client.number > this->max_client_number)
				this->max_client_number = client.number;
			info_clients.push_back(client);
		}

		if (failed)
		{
			failed = false;
			cout << "Not the clients file, please try again" << endl;
			this->info_clients.clear();
			continue;
		}

		fin.close();
	} while (failed); 

	sort(this->info_clients.begin(), this->info_clients.end());
	
	unsigned int max_trans_number = Trans::instance()->getBiggestID();
	max_client_number = (max_trans_number > max_client_number) ? max_trans_number+1 : max_client_number+1;
} 

void Supermarket::Client::removeClient()
{//removes a certain client by removing it from the vector of clients
	vector<Client_t>::iterator it;
	bool removed = false;
	unsigned int sz = info_clients.size(), i = 0;
	string c_name;
	do
	{
		c_name = Input_Asker::instance()->askClientName();
		it = nameBinarySearch(c_name, info_clients);
		if (it->name != c_name)
		{
			cout << "Client not found , please try again " << endl;
			continue;
		}
		else
			break; //keeps asking user an existing name until a correct one is entered
	} while (true);
	info_clients.erase(it);
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
	binaryInsert(new_c, info_clients);
}

void Supermarket::Client::addMoney(const string &S, const double amount)
{
	auto it = nameBinarySearch(S, info_clients);
	it->money += amount;
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
		auto it = nameBinarySearch(client_name, info_clients);
		if (it->name == client_name)
		{
			found = true;
			clientHeader();
			Visualize::instance()->visNumber(it->number); Visualize::instance()->visName(it->name); visMoney(it->money);
			cout << endl;
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

vector<Client_t>::iterator Supermarket::Client::nameBinarySearch(const string &element, vector<Client_t> &vec) const
{
	return vec.begin() + biPos(element, vec, 0, vec.size() - 1);
}

unsigned int Supermarket::Client::biPos(const string &element, const vector<Client_t> &vec, unsigned int start, unsigned int end) const
{
	if (start != end)
	{
		if (element < vec.at((start + end) / 2).name)
			return biPos(element, vec, start, ((end - start) > 1) ? ((start + end) / 2) - 1 : end - 1);
		else if (element > vec.at((start + end) / 2).name)
			return biPos(element, vec, ((start + end) / 2) + 1, end);
		else
			return (start + end) / 2;
	}

	if (start == end && element > vec.at(start).name)
		return start + 1;
	if (start == end && element <= vec.at(start).name)
		return start;

	return 0;
}

string Supermarket::Client::NumtoName(unsigned int num) const
{
	for (auto C : info_clients)
	{
		if (C.number == num)
			return C.name;
	}
	return "";
}
