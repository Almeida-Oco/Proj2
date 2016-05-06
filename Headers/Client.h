#ifndef CLIENT_H
#define CLIENT_H

#include "Declarations.h"
#include "Input_Asker.h"
#include "Visualize.h"
#include "Trans.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class Trans;

using namespace std;

class Client
{
	static string client_file_name;
	static unsigned int max_client_number;
	static vector<Client_t> info_clients;
	static Client *C_pt;

public:
	
	Client() {};
	Client(const Client &C) {};
	//void calcClientMoney(Trans &T);

	vector <Client_t> getInfo() const { return info_clients; }
	void startUp();

	//manipulates vector/info of clients
	void removeClient();
	void addClient();
	void addMoney(const unsigned int c_num, const double amount);
	int findName(const string &c_name);

	//visualize client information
	void visClient();
	void visAllClients();
	void clientHeader();

	void update();


	static Client *instance()
	{
		if (!C_pt)
			C_pt = new Client;
		return C_pt;
	}
private:
	vector<Client_t>::iterator findInsertPos(const Client_t &C) const;
	unsigned int findPos(const Client_t &C, unsigned int start, unsigned int end) const;
	void visMoney(double money);
};

#endif // !STRING
