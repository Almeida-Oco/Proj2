#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include <iostream>
#include <string>

class Supermarket {
private:
	static Supermarket *S_pt;
public:
	//used to avoid multiple class objects
	Supermarket () {};
	Supermarket(const Supermarket &T) {};

	class Visualize;
	class Input_Asker;
	class Bottom_10;
	class Client;
	class Trans;
	class Product;

	void MainMenu();

	static Supermarket *S_instance()
	{
		if (!S_pt)
			S_pt = new Supermarket;
		return S_pt;
	}
private:
	void ClientMenu();
	void TransMenu();
	void AdMenu();
};


#endif // !SUPERMARKET_H