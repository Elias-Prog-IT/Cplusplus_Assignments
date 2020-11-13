/*
	@Author Elias Posluk
	Student-id: elpo14
	@date 2015-02-15
	Assignment 1
	Blekinge Tekniska Högskola
*/

#ifndef CELLURARPHONESTOCK_H
#define CELLURARPHONESTOCK_H

#include <string>
#include <iostream>
#include "CellurarPhone.h"
#include "CellularPhoneStock.h"

using namespace std;

class CellularPhoneStock
{

private:
	static const int SIZE = 30;
	CellurarPhone *Phone[SIZE]; // Ger addressen null. Får inget 'skräp'
	int nrOfCellPhones = 0;



public:
	CellularPhoneStock();
	CellularPhoneStock(const CellularPhoneStock &obj);
	~CellularPhoneStock();

	//CellurarPhoneStock::CellurarPhoneStock();
	void addNewCell(string cellName, string cellColour, int cellInStock, double cellPrice, int &nrOfCellPhones);
	bool alreadyInMemory(string name, string colour, int nrOfCellPhones);
	string showAllCellPhones(int nrOfCellPhones)const;
	string showSpecificCellPhones(string cellName, int position)const;
	string showAllCellPhonesByPriceOrder(double cellPrice, int thisPosition)const;
	bool removeCellPhone(string cellName, string cellColour, int &nrOfCellPhones);
	void updateCellStock(string cellName, string cellColour, int cellStock, double cellPrice, int getMemoryPlace);


	//Get funktion
	int getNrOfCellPhones()const;
	void setNrOfCellPhones(int c);
	int getSIZE()const;

	//Tilldelnings operator
	CellularPhoneStock& operator=(const CellularPhoneStock &in);


	//bool operator==(const CellurarPhoneStock d);
};
#endif 

CellularPhoneStock::CellularPhoneStock(const CellularPhoneStock & obj)
{
}
