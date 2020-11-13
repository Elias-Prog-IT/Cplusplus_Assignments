/*
	@Author Elias Posluk
	Student-id: elpo14
	@date 2015-02-15
	Assignment 1
	Blekinge Tekniska Högskola
*/

#pragma once
#ifndef CELLURARPHONE_H
#define CELLURARPHONE_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class CellurarPhone
{

private:
	string cellName;
	string cellColour;
	double cellPrice;
	int cellInStock;

public:
	CellurarPhone(string cellName, string cellColour, int cellInStock, double cellPrice);

	//Default konstruktor
	CellurarPhone();

	//Destruktor
	~CellurarPhone(); // destruktor exekveras när objektet "upphör" att existera

	//Medlemsfunktioner är ALLA nedanför
	void show() const;

	//Set funktioner 
	void setCellName(string cellName);
	void setCellColour(string Colour);
	void setCellPrice(double cellPrice);
	void setCellInStock(int cellInStock);

	//get funktioner
	string getName()const;
	string getColour()const;
	int getCellInStock()const;
	double getCellPrice()const;

	// sätter samman alla medlemsvariablers värden till en sträng som returneras.
	string toString() const;

	//Operatorer
	CellurarPhone& operator=(const CellurarPhone &in);
	bool operator==(const CellurarPhone c);
	bool operator<(const CellurarPhone c);
	bool operator<=(const CellurarPhone c);


};
#endif


