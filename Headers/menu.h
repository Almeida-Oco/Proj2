#ifndef MENU_H
#define MENU_H

#include "..\Headers\Client.h"
#include "..\Headers\Trans.h"
#include "..\Headers\Product.h"
//Pretty straightforward functions
void ClientMenu(Client &C);
void TransMenu(Trans &T, Client &C, Product &P);
void MainMenu(Client &Cl, Product &P, Trans &T);

//alteracao

#endif // !MENU_H
