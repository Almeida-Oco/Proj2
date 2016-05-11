

//FUNCAO QUE DA O ELEMENTO QUE APARECE MAIS VEZES NOS CLIENTES PARECIDOS COM O CLIENTE ALVO E O CLIENTE ALVO AINDA NAO TEM //
string maximu(vector<string>v, vector<Product>v_prod)
{
	int u = 0, i = 0, max = 0, counter = 0, max_pos=0;
	string product_wanted;
	
	while (u < v_prod.size())
	{

		while (i < v.size())            //this function gives me the name of the product that appears most times in a vector
		{
			if (v_prod[u].prod == v[i])
				counter++;
			i++;
		}
		if (counter > max)
		{
			max_pos = u;
			max = counter;
		}

		i = 0;
		counter = 0;
		u++;
		}

	product_wanted = v_prod[max_pos].prod;
	
	return product_wanted;
}


int searchID_transactions(vector<Transaction> &v_trans, int p)
{
	int i = 0;

	while (i<v_trans.size())
	{
		if (v_trans[i].id == p)         //with this function, I can know the line I should access in the bidimensional vector that I create in Func11.
		{
			return i;
		}
		else
			i++;
	}

	return -1;
}





//FUNC11 É AQUELA QUE FAZ A PUBLICIDADE EM SI,É ELA QUE CONSTROI A MATRIZ E QUE VERIFICA QUAIS OS CLIENTES PARECIDOS COM O CLIENTE ALVO
//E QUAL OS PRODUTOS DESTES QUE O ALVO AINDA NAO TEM ///

void Func11(vector<Transaction> &v_trans, vector <Product>v_prod)
{
	vector< vector<bool> > publi(v_trans.size(), vector<bool>(v_prod.size()));

	vector<bool> vec_bool;


	int i = 0, u = 0, p = 0;

	bool verifi = false; //its a verifier that proves if the product in the list of products was bought by the client or not


	while (p < v_trans.size())
	{


		while (u < v_prod.size())
		{

			while (i < v_trans[p].prod.size())
			{
				if (v_prod[u].prod == v_trans[p].prod[i])
				{
					vec_bool.push_back(true);
					verifi = true;
					break;
				}

				i++;
			}

			if (verifi == false)
			{
				vec_bool.push_back(false);
			}
			verifi = false;
			u++;
			i = 0;


		}

		u = 0;
		publi[p] = vec_bool;
		vec_bool.clear();
		p++;

	}

	int max = -1, compare = 0;
	int id, line = 0, column = 0;
	int same_products = 0;                  
	vector <bool> vec_client_wanted;
	vector <string> vec_different_prod, vec_different_prod_aux;
	string product_wanted;


	cout << "ID: ";
	cin >> id;

	int position = searchID_transactions(v_trans, id);

	while (position == -1)
	{
		cout << "Wrong ID, try again" << endl;
		Func11(v_trans, v_prod);
	}

	vec_client_wanted = publi[position];

	while (line < publi.size())
	{

		while (column < v_prod.size())
		{
			
			if (publi[line][column] && vec_client_wanted[column])
				compare++;                                             // In here I can see how many products does each line have in common with the client I chose and put in a vector of string the products that the client doesn't has
			else
			{

				if ((publi[line][column] == true) && (vec_client_wanted[column] == false))
				{
					vec_different_prod_aux.push_back(v_prod[column].prod);
					same_products=1;
				}

			}

			column++;

		}   
		                                            // same_products helps to prevent that 2 clients with exactly the same transactions are used in this program, because we will choose a product from a client that is similar to the one we chosen but with at least one different product in his/her transaction
		if ( (compare < max) || (line==position) || (same_products==0) )
			vec_different_prod_aux.clear();
		else
		{
			if (compare > max)
			{
				vec_different_prod.clear();
				vec_different_prod = vec_different_prod_aux;
				vec_different_prod_aux.clear();
				max = compare;
			}
			else
			{
				vec_different_prod.insert(vec_different_prod.end(), vec_different_prod_aux.begin(), vec_different_prod_aux.end());
				vec_different_prod_aux.clear();
			}
		}
		compare = 0;
		column = 0;
		same_products = 0;
		line++;

	}

	product_wanted = maximu(vec_different_prod, v_prod);

	cout << "The client " << id << " should be advertised with this product: " << product_wanted << endl;

}

