# Proj2
Vende ++

O QUE FALTA FAZER:

Evitar que o programa crashe ao inserir CTRL+Z ou outro input jabardolas nas funcoes de Input_Asker. 
(algumas acho que ja estao)

Conferir erros que ocorrem, principalmente relacionados com erros de escrita e acesso a posições "out of arrange".

O QUE JÁ ESTÁ FEITO:
Já da para jabardar com o menu q em principio nao vacila, (CONVEM TESTAR).

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--------------------//////////////////////////////////////////
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\SUPERMARKET VENDE ++//////////////////////////////////////////
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\--------------------//////////////////////////////////////////

**SPECIFICATIONS :**

 * For testing purposes, the Bottom 10 reccomendation system contains a variable name N_COMMON, present
 	in the Bottom_10.h file,
 		N_COMMON = 10  ---> Bottom 10
 		N_COMMON = 7  ----> Bottom 7
 		N_COMMON = 3  ----> Bottom 3
 	this is useful since it allows us to test the program without needing to create big amounts of data

 * In the Bottom 10 reccomendation system, we did not use maps or multimaps, and instead used a 
 	vector of pairs, so that we could order it by value and not by key, which makes it easier to
 	find the Bottom 10, since they will be the first 10 costumers.

 * The client information set is sorted by Name.

 * The transaction information set is sorted by Date.

 * The products map, obviously is sorted by Name, and it links the name of product to its price.

 * Everytime the program asks the user to input a reference the a certain client, it is always done
 	by referencing their name and never the number for efficiency reasons.

 * Everytime information is asked to the user it always as a way to cancel, usually by inputting CTRL+Z.

 * All the classes in this program follow the singleton design pattern, meaning only one instance of the 
 	class can exist at all times.

 * All the information changed during runtime, like removing client or adding a transaction, is lost if the
 	program is closed, unless closed by going to the Main Menu and selecting the exit option.


