/*
	@Author Elias Posluk
	Student-id: elpo14
	@date 2015-02-15
	Assignment 1
	Blekinge Tekniska Högskola
*/

#include <iostream>
#include <string>
#include "CellularPhoneStock.h"
#include <crtdbg.h>
using namespace std;

//prototyper
void addNewCell(CellularPhoneStock &obj, int &nrOfCellPhones);
void showSpecificCellPhones(CellularPhoneStock &obj, int nrOfCellPhones);
void showAllCellPhonesByPriceOrder(CellularPhoneStock &obj, int nrOfCellPhones);
void showAllCellPhones(CellularPhoneStock &obj, int nrOfCellPhones);
void removeCellPhone(CellularPhoneStock &obj, int &nrOfCellPhones);
int menu();

// Main 
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //kollar upp minnes läckor.

	int choice = 0, nrOfCellPhones = 0; // variabler

	CellularPhoneStock obj;				// kallar till objecten i Stock.h. 

	do								//Kör menun.
	{
		choice = menu();
		if (cin.good())
		{
			if (choice < 0)
			{
				cout << " You typed in an invalid option! Try again! " << endl;
			}
			else if (choice == 1)
			{
				addNewCell(obj, nrOfCellPhones);
			}
			else if (choice == 2)
			{
				showAllCellPhones(obj, nrOfCellPhones);
			}
			else if (choice == 3)
			{
				showAllCellPhonesByPriceOrder(obj, nrOfCellPhones);
			}
			else if (choice == 4)
			{
				showSpecificCellPhones(obj, nrOfCellPhones);
			}
			else if (choice == 5)
			{
				removeCellPhone(obj, nrOfCellPhones);
			}
			else if (choice > 5)
			{
				std::cout << " You typed in an invalid option! Try again! " << endl;
			}
		}
		else
		{

			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');//Får den att inte 'flasha' till flera gånger. När man skriver en längre sträng. 
			std::cin.clear();
		}
	} while (choice != 0);


	getchar();
	return 0;
}



//Funktioner till prototyper
int menu() //funktionerna till menun
{
	int choice = 0;
	std::cout << "1. Add a new cellular phone to the stock." << endl;
	std::cout << "2. Show all cell phones in the stock." << endl;
	std::cout << "3. Show all cellphones in stock, below the givin value" << endl;
	std::cout << "4. Present all cellular phones in the stock of a certain name." << endl;
	std::cout << "5. Remove a cellular phone from the stock given the name and the color." << endl;
	std::cout << "0. Exit." << endl;
	std::cout << "Choice: "; std::cin >> choice;
	return choice;
}
void addNewCell(CellularPhoneStock &obj, int &nrOfCellPhones) //Funktionen som lägger till telefon, pris, färg, mm.
{
	string newName, newColour;
	double newPrice;
	int newStock;

	std::cin.ignore();
	system("cls");
	std::cout << "Enter the new phone name: "; getline(cin, newName);
	std::cout << "Enter the new phone colour: "; getline(cin, newColour);

	if (obj.alreadyInMemory(newName, newColour, nrOfCellPhones) == false)
	{
		std::cout << "Enter the new phone price: "; std::cin >> newPrice;
		std::cout << "Enter the quantity to stock: "; std::cin >> newStock;
		obj.addNewCell(newName, newColour, newStock, newPrice, nrOfCellPhones);
		obj.setNrOfCellPhones(nrOfCellPhones);
	}
	else
	{
		char updateYesOrNo;
		std::cout << "The phone name is already registered in the memory!" << endl;
		std::cout << "Do you want to update the stock for the phone? Y/N: "; std::cin >> updateYesOrNo;

		if (updateYesOrNo == 'y' || updateYesOrNo == 'Y') //Frågar om man vill utöka antalet i lager för telefonen i fråga.
		{
			cout << "Enter the new phone price: "; cin >> newPrice;
			cout << "Enter the quantity to stock: "; cin >> newStock;

			int getMemoryPlace;
			for (int i = 0; i < nrOfCellPhones; i++)
			{

				if (obj.alreadyInMemory(newName, newColour, nrOfCellPhones) == true)
				{
					getMemoryPlace = i;
				}
			}
			obj.updateCellStock(newName, newColour, newStock, newPrice, getMemoryPlace);
		}
		else
		{	//Does nothing
		}
	}
}
void showSpecificCellPhones(CellularPhoneStock &obj, int nrOfCellPhones)//letar upp en specific telefon som man anger.
{
	string findName;

	cin.ignore();
	cout << endl;
	cout << "Name the cell you want to find: "; getline(cin, findName); // Frågar efter vilken telefon man söker, sen körs funktionen till den.
	cout << endl;
	for (int i = 0; i < nrOfCellPhones; i++)
	{
		cout << obj.showSpecificCellPhones(findName, i);
	}
}
void showAllCellPhonesByPriceOrder(CellularPhoneStock &obj, int nrOfCellPhones)//Funktion som kollar upp max priset som anges, och skriver ut dem priserna som är = priset som angavs, samt priserna under.
{
	double findPrice;

	cout << endl;
	std::cout << "Enter your maximum price range limit for a phone: "; cin >> findPrice;
	std::cout << endl;
	for (int i = 0; i < nrOfCellPhones; i++)
	{
		std::cout << obj.showAllCellPhonesByPriceOrder(findPrice, i);
	}
}
void showAllCellPhones(CellularPhoneStock &obj, int nrOfCellPhones)//Visar alla telefoner som har skrivits in samt sparats i arrayen. 
{
	std::cout << endl;
	for (int i = 0; i < nrOfCellPhones; i++)
	{
		std::cout << obj.showAllCellPhones(i);
	}
}
void removeCellPhone(CellularPhoneStock &obj, int &nrOfCellPhones)//Tar bort telefonen från minnesplatsen, som man anger med namn, samt färg. 
{
	CellurarPhone temp;
	string removePhoneName, removePhoneColour;
	std::cin.ignore();
	std::cout << endl;
	std::cout << "What phone do you want to remove?: "; getline(cin, removePhoneName);
	std::cout << "What colour does the phone have?: "; getline(cin, removePhoneColour);
	if (obj.removeCellPhone(removePhoneName, removePhoneColour, nrOfCellPhones) == true)
	{
		std::cout << endl;
		std::cout << "The Phone was removed succesfully!" << endl;
	}
	else
	{
		std::cout << endl;
		std::cout << "The Phone wasn't removed succesfully!" << endl << endl;
	}
}