/*
	@Author Elias Posluk
	Student-id: elpo14
	@date 2015-02-15
	Assignment 1
	Blekinge Tekniska Högskola
*/

#include "CellurarPhone.h"

using namespace std;


// DEFINITIONEN

CellurarPhone::CellurarPhone(string cellName, string cellColour, int cellInStock, double cellPrice)
{
	this->cellName = cellName;
	this->cellColour = cellColour;
	this->cellInStock = cellInStock;
	this->cellPrice = cellPrice;
}

CellurarPhone::CellurarPhone()
{
	this->cellName = "Unknown";
	this->cellColour = "Unknown";
	this->cellInStock = 0;
	this->cellPrice = 0.00;
}

//Void, Klassen CellurarPhone scoopoperatiorn (::) och sedan funktionen

//To string
string CellurarPhone::toString()const
{
	stringstream stringCall;
	stringCall << "Phone name: " << this->cellName << endl
		<< "Phone colour: " << this->cellColour << endl
		<< "Cell phone price: " << this->cellPrice << endl
		<< "stock: " << this->cellInStock << endl << endl;
	return stringCall.str();
}

//set funktioner
void CellurarPhone::setCellName(string cellName)
{
	this->cellName = cellName;
}

void CellurarPhone::setCellColour(string cellColour)
{
	this->cellColour = cellColour;
}

void CellurarPhone::setCellPrice(double cellPrice)
{
	this->cellPrice = cellPrice;
}

void CellurarPhone::setCellInStock(int cellInStock)
{
	this->cellInStock = cellInStock;
}

//get funktioner
string CellurarPhone::getName()const
{
	return this->cellName;
}

string CellurarPhone::getColour()const
{
	return this->cellColour;
}

int CellurarPhone::getCellInStock()const
{
	return this->cellInStock;
}

double CellurarPhone::getCellPrice()const
{
	return this->cellPrice;
}

CellurarPhone::~CellurarPhone()//destruktor
{
}
CellurarPhone& CellurarPhone::operator=(const CellurarPhone &in)
{
	this->cellName = in.cellName;
	this->cellColour = in.cellColour;
	this->cellInStock = in.cellInStock;
	this->cellPrice = in.cellPrice;
	return *this;
}
bool CellurarPhone::operator==(const CellurarPhone c)
{
	return this->cellName == c.cellName && this->cellColour == c.cellColour;
}
bool CellurarPhone::operator<(const CellurarPhone c)
{
	return this->cellPrice < c.cellPrice;
}
bool CellurarPhone::operator<=(const CellurarPhone c)
{
	return this->cellPrice <= c.cellPrice;
}

