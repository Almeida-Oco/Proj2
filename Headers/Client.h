#ifndef CLIENT_H
#define CLIENT_H

#include "Declarations.h"
#include "Supermarket.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class Trans;
class Supermarket;

class Supermarket::Client
{
	static std::string client_file_name;
	static unsigned int max_client_number;
	static std::vector<Client_t> info_clients;
	static Client *C_ptr;

public:
	
	Client() {};
	Client(const Client &C) {};
	//void calcClientMoney(Trans &T);

	std::vector <Client_t> getInfo() const { return info_clients; }
	void startUp();

	//manipulates vector/info of clients
	void removeClient();
	void addClient();
	void addMoney(const unsigned int c_num, const double amount);
	int findName(const std::string &c_name);

	//visualize client information
	void visClient();
	void visAllClients();
	void clientHeader();

	void update();


	static Client *instance()
	{
		if (!C_ptr)
			C_ptr = new Client;
		return C_ptr;
	}
private:
	std::vector<Client_t>::iterator findInsertPos(const Client_t &C) const;
	unsigned int findPos(const Client_t &C, unsigned int start, unsigned int end) const;
	void visMoney(double money);
};

#endif // !STRING
