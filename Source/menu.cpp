#include "..\Headers\menu.h"
//i think the functions are pretty self-explanatory
/*
void Supermarket::MainMenu()
{
	const int C = 1, Tr = 2, A = 3, E = 0;
	int action;
	do
	{
		cout << endl << "========================================================" << endl;
		cout << "Where do you want to go? " << endl;
		cout << endl;
		cout << "0 -> Exit" << endl;
		cout << "1 -> Clients" << endl;
		cout << "2 -> Transactions" << endl;
		cout << "3 -> Advertisement" << endl;
		cout << "---> ";
		cin >> action;
		cin.ignore(999, '\n');
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(9999, '\n');
		}
		if (action == C)
			ClientMenu();
		else if (action == Tr)
			TransMenu();
		else if (action == A)
			Trans::instance()->selectiveAd();
		else if (action == E)
			break;
		else
			cout << "Invalid input, please try again";
	} while (action != E);
}

void Supermarket::ClientMenu()
{
	const int add = 1, rem = 2, see_one = 3, see_all = 4, go_back = 0;
	int action;
	do
	{
		cout << endl << "========================================================" << endl;
		cout << "What do you want to do?" << endl;
		cout << endl;
		cout << "0 -> Go Back" << endl;
		cout << "1 -> Add Client" << endl;
		cout << "2 -> Remove Client" << endl;
		cout << "3 -> See Client" << endl;
		cout << "4 -> See  all Clients" << endl;
		cout << "---> ";
		cin >> action;
		cin.ignore(999, '\n');
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(9999, '\n');
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
			cout << "Invalid input, please try again" << endl << endl;
	} while (action != go_back);
}

void Supermarket::TransMenu()
{
	cout << endl << "========================================================" << endl;
	const int add = 1, see_c = 2, see_d = 3, see_b = 4, see_all = 5, go_back = 0;
	int action;
	do
	{
		cout << "What do you want to do?" << endl;
		cout << endl;
		cout << "0 -> Go back" << endl;
		cout << "1 -> Add Transaction" << endl;
		cout << "2 -> See Client Transaction" << endl;
		cout << "3 -> See Day Transactions" << endl;
		cout << "4 -> See Transactions between dates" << endl;
		cout << "5 -> See  all Transactions" << endl;
		cout << "---> ";
		cin.clear();
		cin >> action;
		cin.ignore(999, '\n');
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(9999, '\n');
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
			cout << "Invalid input, please try again" << endl << endl;
	} while (action != go_back);
}
*/