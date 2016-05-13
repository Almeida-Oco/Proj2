#include "..\Headers\Supermarket.h"
#include "..\Headers\Client.h"
#include "..\Headers\Product.h"
#include "..\Headers\Visualize.h"
#include "..\Headers\Bottom_10.h"
#include "..\Headers\Input_Asker.h"
#include "..\Headers\Trans.h"

using namespace std;

void Supermarket::MainMenu()
{
	const int C = 1, Tr = 2, A = 3, E = 0;
	int action;
	do
	{
		std::cout << std::endl << "========================================================" << std::endl;
		std::cout << "Where do you want to go? " << std::endl;
		std::cout << std::endl;
		std::cout << "0 -> Exit" << std::endl;
		std::cout << "1 -> Clients" << std::endl;
		std::cout << "2 -> Transactions" << std::endl;
		std::cout << "3 -> Advertisement" << std::endl;
		std::cout << "---> ";
		std::cin >> action;
		std::cin.ignore(999, '\n');
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(9999, '\n');
		}
		if (action == C)
			ClientMenu();
		else if (action == Tr)
			TransMenu();
		else if (action == A)
			Supermarket::Trans::instance()->selectiveAd();
		else if (action == E)
			break;
		else
			std::cout << "Invalid input, please try again";
	} while (action != E);
}

void Supermarket::ClientMenu()
{
	const int add = 1, rem = 2, see_one = 3, see_all = 4, go_back = 0;
	int action;
	do
	{
		std::cout << std::endl << "========================================================" << std::endl;
		std::cout << "What do you want to do?" << std::endl;
		std::cout << std::endl;
		std::cout << "0 -> Go Back" << std::endl;
		std::cout << "1 -> Add Client" << std::endl;
		std::cout << "2 -> Remove Client" << std::endl;
		std::cout << "3 -> See Client" << std::endl;
		std::cout << "4 -> See  all Clients" << std::endl;
		std::cout << "---> ";
		std::cin >> action;
		std::cin.ignore(999, '\n');
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(9999, '\n');
		}

		if (action == add)
			Client::instance()->addClient();
		else if (action == rem)
			Client::instance()->removeClient();
		else if (action == see_one)
			Client::instance()->visClient();
		else if (action == see_all)
			Client::instance()->visAllClients();
		else
			std::cout << "Invalid input, please try again" << std::endl << std::endl;
	} while (action != go_back);
}

void Supermarket::TransMenu()
{
	std::cout << std::endl << "========================================================" << std::endl;
	const int add = 1, see_c = 2, see_d = 3, see_b = 4, see_all = 5, go_back = 0;
	int action;
	do
	{
		std::cout << "What do you want to do?" << std::endl;
		std::cout << std::endl;
		std::cout << "0 -> Go back" << std::endl;
		std::cout << "1 -> Add Transaction" << std::endl;
		std::cout << "2 -> See Client Transaction" << std::endl;
		std::cout << "3 -> See Day Transactions" << std::endl;
		std::cout << "4 -> See Transactions between dates" << std::endl;
		std::cout << "5 -> See  all Transactions" << std::endl;
		std::cout << "---> ";
		std::cin.clear();
		std::cin >> action;
		std::cin.ignore(999, '\n');
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(9999, '\n');
		}

		if (action == add)
			Trans::instance()->addTrans();
		else if (action == see_c)
			Trans::instance()->visClientTrans();
		else if (action == see_d)
			Trans::instance()->visDayTrans();
		else if (action == see_b)
			Trans::instance()->visBetweenDates();
		else if (action == see_all)
			Trans::instance()->visAllTrans();
		else
			std::cout << "Invalid input, please try again" << std::endl << std::endl;
	} while (action != go_back);
}

void Supermarket::AdMenu()
{
	const int E = 0, C_a = 1, B_a = 2;
	int action;
	do
	{
		std::cout << std::endl << "========================================================" << std::endl;
		std::cout << "Where do you want to go? " << std::endl;
		std::cout << std::endl;
		std::cout << "0 -> Go Back" << std::endl;
		std::cout << "1 -> Client Advertisement" << std::endl;
		std::cout << "2 -> Bottom 10 Advertisement" << std::endl;
		std::cout << "---> ";
		std::cin >> action;
		std::cin.ignore(999, '\n');
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(9999, '\n');
		}
		if (action == C_a)
			Supermarket::Trans::instance()->selectiveAd();
		else if (action == B_a)
			Supermarket::Bottom_10::instance()->Source();
		else if (action == E)
			break;
		else
			std::cout << "Invalid input, please try again";
	} while (action != E);
}