#ifndef MENU_H
#define MENU_H

#include "Client.h"
#include "Trans.h"
#include "Product.h"
//Pretty straightforward functions
void ClientMenu(Client &C);
void TransMenu(Trans &T, Client &C, Product &P);
void MainMenu(Client &Cl, Product &P, Trans &T);
void ProdMenu(Product &P);

#endif // !MENU_H
