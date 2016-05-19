#ifndef CLIENT_H
#define CLIENT_H

#include "Declarations.h"
#include "Supermarket.h"
#include <iostream>
#include <set>
#include <iomanip>
#include <cassert>
#include <string>
#include <fstream>

class Trans;

class Supermarket::Client
{
	/*		   	
	* DATA MEMBERS
	*/
	unsigned int number_lines_cli;  
	std::string client_file_name;
	unsigned int max_client_number;
	std::set<Client_t> info_clients;
	static Client *C_ptr;
public:
	//used to avoid multiple class objects
	Client() {};
	Client(const Client &C) {};

	/*
	*  MAIN MEMBER FUNCTIONS
	*/
	std::set<Client_t>::iterator nameBinarySearch(const std::string &element); 
	//iterates the set to find the client by its name
	std::string NumtoName(unsigned int num) const;
	//gets the client name based on the given ID
	void startUp();
	//used to initialize the set and etc.

	//manipulates vector/info of clients
	void removeClient();
	void addClient();
	void addMoney(const std::string &S, const double amount);

	//visualize client information
	void visClient();
	void visAllClients();
	void clientHeader();

	void update();
	std::set<Client_t> &getInfo(); //returns info_clients

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
