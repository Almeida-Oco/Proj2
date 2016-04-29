#ifndef CLIENT_H
#define CLIENT_H

#include "..\Headers\Declarations.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Visualize.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//sadnasçnasnf

using namespace std;

vector<string> string_split(const string &line, const string spliter);
//similar to java string_split, given a string and a spliter, it returns the different parts of the original string in a vector

string remove_middle_spaces(const string &S);
//leaves only one middle space between the different words there might exist

string trim(string &str);
//removes all spaces at the left and at the right of the string

bool testText(const string &c_name);
//checks if text only contains letters and spaces

class Client
{
	static string client_file_name;
	static unsigned int max_client_number;
	//used to avoid number repetitions
public:
	static vector<Client_t> info_clients;
	Client();

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
	void visMoney(double money);
};

#endif // !STRING
