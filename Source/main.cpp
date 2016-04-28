#include <climits>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//FUNCTIONS AND ETC
#include "Declarations.h"
#include "Product.h"
#include "Visualize.h"
#include "Client.h"
#include "Trans.h"
#include "Input_Asker.h"
#include "menu.h"

bool testText(const string &c_name);
//checks if the string contains only letters and spaces and if so return true

void update_n_exit(Client &info_clients, Product &info_prod, Trans &info_trans);
//last function to be called, updates the files, according to the current information on the info_(vectors)



int main()
{
	Client C;
	Product P;
	Trans T;
	MainMenu(C, P, T);
	update_n_exit(C, P, T);
}

void update_n_exit(Client &C, Product &P, Trans &T)
{
	C.update();
	P.update();
	T.update();
	cout << "GOODBYE" << endl;
	exit(0);
}


//====================================================================================
//===================================== STRING =======================================
//====================================================================================
vector<string> string_split(const string &line, const string spliter)
{
	unsigned int pos_spliter = 0, cont_spliter = 0, sz = line.size(), splt_sz = spliter.size(), inicio = 0;
	vector<string> split_string;

	for (unsigned int i = 0; i < sz; i++)
	{
		if (i == sz - 1)
		{
			pos_spliter = i + 1;
			split_string.push_back(line.substr(inicio, pos_spliter - inicio));
			break;
		}

		if (line.at(i) == spliter.at(cont_spliter))
		{
			if (cont_spliter != splt_sz)
				cont_spliter++;
			if (cont_spliter == splt_sz)
			{
				pos_spliter = i - (splt_sz-1);
				split_string.push_back(line.substr(inicio, pos_spliter - inicio));
				inicio = pos_spliter + 1;
				inicio = i + 1;
				cont_spliter = 0;
			}
		}
	}
	return split_string;
}

string remove_middle_spaces(const string &S)
{//receives trimmed string with only spaces in the middle, and returns a string that contains only 1 space between names
	string final_string;
	bool space = false;

	for (char c : S)
	{
		if (c != ' ')
		{
			final_string.push_back(c);
			space = true;
			continue;
		}
		else
		{
			if (space)
				final_string.push_back(' ');
			space = false;
		}
	}
	return final_string;
}

string trim(string &str)
{
	size_t first = -1;
	size_t last = -1;
	first = str.find_first_not_of(' ');
	last = str.find_last_not_of(' ');
	if (first != ULONG_MAX && last != ULONG_MAX)
		return remove_middle_spaces(str.substr(first, (last - first + 1)));
	else
		return "";
}

//====================================================================================
//=============================== MISCELLANEOUS ======================================
//====================================================================================

bool testText(const string &c_name) 
{
	for (char i : c_name)
	{
		if (!((i >= A && i <= Z) || (i >= a && i <= z) || i == SPACE))
			return false;
	}
	return true;
}

void qksort(vector<int> &qsort_vetor, int esquerda, int direita) {
	int pos_pivot = (direita - esquerda) / 2 + esquerda, i;
	int fim = direita, inicio = esquerda;

	for (i = esquerda; i <= fim; i++)
	{
		if (qsort_vetor[i] > qsort_vetor[pos_pivot])
		{
			if (fim == pos_pivot)
				pos_pivot = i;
			swap(qsort_vetor[i], qsort_vetor[fim]);
			i--;
			fim--;
			continue;
		}
		if (qsort_vetor[i] < qsort_vetor[pos_pivot] && i>pos_pivot)
		{
			if (inicio == pos_pivot)
				pos_pivot = i;
			swap(qsort_vetor[i], qsort_vetor[inicio]);
			i--;
			inicio++;
		}
		/*
		if (i > pos_pivot) {
		swap(qsort_vetor[i], qsort_vetor[pos_pivot]);
		pos_pivot = i;
		}
		*/
	}
	if (direita > pos_pivot + 1)
		qksort(qsort_vetor, (pos_pivot + 1), direita);

	if (esquerda < pos_pivot - 1 && pos_pivot != 0)
		qksort(qsort_vetor, esquerda, (pos_pivot - 1));
}

void quicksort(vector<int> &qs) {
	qksort(qs, 0, qs.size() - 1); //my implementation of quicksort
}