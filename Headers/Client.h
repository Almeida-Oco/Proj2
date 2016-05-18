#ifndef CLIENT_H
#define CLIENT_H

#include "Declarations.h"
#include "Supermarket.h"
#include "Binary_Op.h"
#include <iostream>
#include <set>
#include <iomanip>
#include <cassert>
#include <string>
#include <fstream>

class Trans;

class Supermarket::Client
{
	template <typename T> friend unsigned int findPos(const T &element, const std::vector<T> &vec, unsigned int start, unsigned int end);
	template <typename T> friend void binaryInsert(const T &element, std::vector<T> &vec);

	unsigned int number_lines_cli;  
	std::string client_file_name;
	unsigned int max_client_number;
	std::set<Client_t> info_clients;
	static Client *C_ptr;
public:
	
	Client() {};
	Client(const Client &C) {};

	std::set<Client_t> getInfo() const;
	std::set<Client_t>::iterator nameBinarySearch(const std::string &element);
	std::string NumtoName(unsigned int num) const;
	void startUp();

	//manipulates vector/info of clients
	void removeClient();
	void addClient();
	void addMoney(const std::string &S, const double amount);

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
	void visMoney(double money);
};

#endif // !STRING
