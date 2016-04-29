#include "..\Headers\menu.h"
//i think the functions are pretty self-explanatory
void MainMenu(Client &Cl, Product &P, Trans &T)
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
			ClientMenu(Cl);
		else if (action == Tr)
			TransMenu(T, Cl, P);
		else if (action == A)
			T.selectiveAd(Cl);
		else if (action == E)
			break;
		else
			cout << "Invalid input, please try again";
	} while (action != E);
}

void ClientMenu(Client &C)
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
			C.addClient();
		else if (action == rem)
			C.removeClient();
		else if (action == see_one)
			C.visClient();
		else if (action == see_all)
			C.visAllClients();
		else
			cout << "Invalid input, please try again" << endl << endl;
	} while (action != go_back);
}

void TransMenu(Trans &T , Client &C , Product &P)
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
			T.addTrans(P,C);
		else if (action == see_c)
			T.visClientTrans(C);
		else if (action == see_d)
			T.visDayTrans();
		else if (action == see_b)
			T.visBetweenDates();
		else if (action == see_all)
			T.visAllTrans();
		else
			cout << "Invalid input, please try again" << endl << endl;
	} while (action != go_back);
}