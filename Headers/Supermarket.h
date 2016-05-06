#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include "Declarations.h"
#include "Client.h"
#include "menu.h"
#include "Trans.h"
#include "Product.h"
#include "Visualize.h"



class Supermarket {
private:
	std::multimap<Client_t, Trans_t > CtoT;
	Client C;
	Trans T;
	Product P;

public:
	Supermarket();



};


#endif // !SUPERMARKET_H