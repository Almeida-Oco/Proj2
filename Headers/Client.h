#ifndef CLIENT_H
#define CLIENT_H

#include "..\Headers\Declarations.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Visualize.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

//sadnasçnasnf

using namespace std;

vector<string> string_split(const string &line, const string spliter);
string remove_middle_spaces(const string &S);
string trim(string &str);
bool testText(const string &c_name);


class Client
{
	static string client_file_name;
	static unsigned int max_client_number;
	static vector<Client_t> info_clients;
public:
	
	Client();

	vector <Client_t> getInfo() const { return info_clients; }

	//manipulates vector/info of clients
	void removeClient();
	void addClient();
	void addMoney(const unsigned int c_num, const double amount);
	int findName(const string &c_name);
	//returns position in info_clients of given name, or returns -1 if not found

	//visualize client information
	void visClient();
	void visAllClients();
	void clientHeader();

	void update();
private:
	vector<Client_t>::iterator findInsertPos(const Client_t &C) const;
	unsigned int findPos(const Client_t &C, unsigned int start, unsigned int end) const;
	void visMoney(double money);
};

#endif // !STRING
