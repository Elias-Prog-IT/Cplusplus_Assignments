/*
	@Author Elias Posluk
	Student-id: elpo14
	@date 2015-10-07
	T�rningsspel
	H�gskolan i Sk�vde
*/
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

//Funktiondeklaration
int menu();
void playNewGame(string name, int &balance, int betMoney, int deposit, int userScore, int pcScore);
void showBalance(int &balance);
void readFromFile(string &name, int &balance);
void exitGame();

int main()
{
	int deposit = 0, betMoney = 0, balance = 0;
	int userScore = 0, pcScore = 0;
	int choice = 0;

	string name;

	srand((unsigned int)time(NULL));// fick varning n�r jag hade srand()(time(0)), s� jag gjorde lite google s�kning och fick fram att man ska ha "unsigned int" f�r att f� bort varningen. 

	//V�lkomstmeddelande, och f�rfr�gar namnet p� spelaren.
	std::cout << "***************************************" << endl;
	std::cout << " ******* " << " Welcome to the dice game! " << " *******" << endl;
	std::cout << "***************************************" << endl;
	std::cout << "What's your name?" << endl;
	cin >> name;
	do																	//Do-while loop som loopar ig�ng menyn till spelet. Menyn inneh�ller 4 val. Samt felmedellande om man v�ljer val som inte finns i menyn.
	{
		choice = menu();
		if (cin.good())
		{
			if (choice < 0)
			{
				std::cout << "You typed in an invalid option! Try again! " << endl; //Felmedellande om man trycker p� allt under siffran 1.
			}
			else if (choice == 1)
			{
				playNewGame(name, balance, betMoney, deposit, userScore, pcScore); //kallelse till funktionen 'playNewGame', som k�r ig�ng spelet.
			}
			else if (choice == 2)
			{
				showBalance(balance);
			}
			else if (choice == 3)
			{
				readFromFile(name, balance);  //kallelse till funktionen 'readFromFile', som sparar spelarens information till textfil.
			}
			else if (choice == 4)
			{
				exitGame(); //kallar p� funktionen, som avslutar spelet.
			}
			else if (choice > 4)
			{
				std::cout << "You typed in an invalid option! Try again! " << endl;//Felmedellande om man trycker p� siffran �ver 4.
			}
		}
	} while (choice != 4);
	system("pause");
	return 0;
}

int menu() //Menun till spelet
{
	int choice = 0;
	std::cout << "1. Play a game " << endl;
	std::cout << "2. Show my balance " << endl;
	std::cout << "3. Save file" << endl;
	std::cout << "4. Exit game " << endl;
	cin >> choice;
	return choice;
}
void readFromFile(string &name, int &balance) //Funktionen som sparar ner information om spelaren.
{
	ofstream outFile;
	outFile.open("DiceGame.txt"); //Textdokumentet som informationen kommer sparas till heter "DiceGame.txt" 
	outFile << "User " << name << " got the amount " << balance << " kr" << std::endl; //Visar spelarens namn samt hur mycket man har p� kontot.
	outFile.close();
	std::cout << "Your information is saved!" << endl; //Ger �terkoppling till spelarn att informationen har sparats.
}
void showBalance(int &balance) // Visar spelarns konto summa. 
{
	std::cout << "Your current balance is: " << balance << " kr" << std::endl;
}
void playNewGame(string name, int &balance, int betMoney, int deposit, int userScore, int pcScore)
{
	int userDie1 = 0, userDie2 = 0;
	int pcDie1 = 0, pcDie2 = 0;
	int firstDice, secondDice, thirdDice, fourthDice;
	int maxAmount = 5000;
	char change = 'y';

	std::cout << "Welcome " << name << " ! " << std::endl; //K�r man ig�ng spelet, s� m�ts man med en h�lsning samt p�minelse p� hur mycket man har i kontot. 
	std::cout << "Your account  balance is " << balance << " kr" << std::endl;
	std::cout << std::endl;

	if (balance <= 0) //Om man inte har pengar i kontot, dvs har 0kr, s� hamnar man h�r, d�r spelaren f�r s�tta in pengar.
	{
		std::cout << "You unfortunately don't have enough money in your account. " << std::endl;
		std::cout << "How much money do you want to deposit? " << std::endl;
		cin >> deposit;
		if (deposit == 100 || deposit == 300 || deposit == 500) // Kollar om spelaren s�tter in r�tt m�ngd pengar som man f�r s�tta in. 
		{
			std::cout << "Your amount to deposit is admited" << std::endl; // F�r �terkoppling att ens ins�ttning har g�tt bra till.
			std::cout << (balance = (balance + deposit)) << std::endl;
		}
		else if (deposit != 100 || deposit != 300 || deposit != 500) //Om man inte s�tter in r�tt m�ngd, s� f�r man felmedellande d�r man f�r �terkoppling om vad som gick fel, samt att kunna g�ra om det igen.
		{
			std::cout << "The entered amount is not an accepted value! " << std::endl;
			std::cout << "Please make a new bet with the amount of either 100kr, 300kr, or 500kr" << std::endl;
			std::cin >> deposit;
			balance = (balance + deposit);
		}
	}
	else if (balance > 0) // Om man har k�rt en omg�ng innan och k�r omspelet, s� hamnar man h�r, om man fortfarande har pengar i kontot. D� blir man tillfr�gad om man vill s�tta in mer pengar i kontot. 
	{							//Svarar man med 'y' eller 'Y', s� g�r man in i  if-satsen d�r man f�r s�tta in pengar. Annars om man v�ljer 'n' eller 'N' s� hamnar man direkt p� bettningen.
		std::cout << "Do you want to do an extra deposit to your account?  (y/n)" << std::endl;
		cin >> change;
		if (change == 'y' || change == 'Y')
		{
			std::cout << "How much money do you want to deposit? " << std::endl;
			cin >> deposit;
			if (deposit + balance < maxAmount)
			{
				if (deposit == 100 || deposit == 300 || deposit == 500) // Kollar om spelaren s�tter in r�tt m�ngd pengar som man f�r s�tta in. 
				{
					std::cout << "Your amount to deposit is admited" << std::endl;
					std::cout << (balance = (balance + deposit)) << std::endl;
				}
				else if (deposit != 100 || deposit != 300 || deposit != 500)  //Om man inte s�tter in r�tt m�ngd, s� f�r man felmedellande d�r man f�r �terkoppling om vad som gick fel, samt att kunna g�ra om det igen.
				{
					std::cout << "The entered amount is not an accepted value! " << std::endl;
					std::cout << "Please make a new bet with the amount of either 100kr, 300kr, or 500kr" << std::endl;
					std::cin >> deposit;
					balance = (balance + deposit);
				}
			}
			else if (maxAmount < balance + deposit) // H�r kommer sp�rren p� 5000kr, if-satsen kollar p� hur mycket du har i kontot, samt hur mycket du vill s�tta in i kontot igen inte �verstiger maxsumman p� kontot.
			{
				std::cout << "Sorry, but you can  only have 5000kr in your account. " << std::endl;
				std::cout << " Your account balance now: " << balance << " kr" << std::endl;
			}
		}
	}
	std::cout << "How much money do you want to bet? " << endl;
	cin >> betMoney;
	if (betMoney == 100 || betMoney == 300 || betMoney == 500)//Checkar av s� att man bettar r�tt m�ngd som �r till�tet
	{
		std::cout << "Your bet is admited" << endl;
		balance = (balance - betMoney);
	}
	else if (betMoney != 100 || betMoney != 300 || betMoney != 500) // Blir en �terkoppling som p�mminer om hur mycket man f�r betta, om man bettar fel summa.
	{
		std::cout << "The entered amount is not an accepted value! " << endl;
		std::cout << "Please make a new bet with the amount of either 100kr, 300kr, or 500kr" << endl;
		cin >> betMoney;
		balance = (balance - betMoney);
	}
	cout << "You betted :" << betMoney << endl;
	std::cout << "Your account balance is now " << balance << endl;
	cout << "Press enter to start rolling your dices' " << endl; //F�r att p�b�rja dicespelet kr�vs att man trycker p� enter
	getchar();
	getchar();
	int i = 0;
	userScore = 0;
	pcScore = 0;
	while (i < 3) // Loopar igenom t�rningskasten max tre g�nger.
	{
		i++;
		firstDice = rand() % 6 + 1;
		std::cout << "Your first dice toss is: " << firstDice << endl << endl;

		secondDice = rand() % 6 + 1;
		std::cout << "Your seconds dice toss is: " << secondDice << endl << endl;

		std::cout << "*************************************************************" << std::endl;
		thirdDice = rand() % 6 + 1;
		std::cout << "Computers first dice is a : " << thirdDice << endl << endl;
		fourthDice = rand() % 6 + 1;
		std::cout << "Computers second dice is a : " << fourthDice << endl << endl;

		if (firstDice > secondDice) //om spelarens f�rsta t�rning �r st�rre �n den andra t�rningen.
		{
			userDie1 = firstDice; //S� hamnar t�rningens summa i variabeln userDie1
		}
		else
		{
			userDie1 = secondDice; //Annars �r spelarens andra t�rning st�rre �n spelarens f�rsta t�rning, och den summan hamnar i variabeln userDie1.
		}
		if (thirdDice > fourthDice)//H�r kollar vi om datorns f�rsta t�rning �r st�rre �n den andra t�rningen.
		{
			pcDie1 = thirdDice;//�r datorns f�rsta t�rning st�rre �n andra t�rningen, s� hamnar datan/summan i variabeln pcDie1.
		}
		else
		{
			pcDie1 = fourthDice;//Om datorns andra t�rning �r st�rre, s� hamnar summan i pcDie1 ist�llet.
		}
		if (userDie1 > pcDie1) //Om spelaren har en h�gre siffra, s� vinner dem rundan
		{
			std::cout << "You have won the round! " << endl;
			userScore++;
		}
		else if (pcDie1 > userDie1)// datorn vinner rundan om dem har h�gre siffra
		{
			std::cout << "You have lost the round! " << endl;
			pcScore++;
		}
		else //om b�gge spelaren och datorn har likadana siffror, s� blir det oavgjort, d�r datorn f�r po�ng.
		{
			std::cout << "*********************" << std::endl;
			std::cout << "It's a TIE! " << endl;
			std::cout << "*********************" << std::endl;
			pcScore++;
		}
		std::cout << "The score is: " << name << ": " << userScore << " " << "computer: " << pcScore << endl << endl; // �terkoppling p� hur m�nga po�ng man har efter rundorna
		if (pcScore == 2) //Om datorn har vunnit tv� rundor i rad, s� avslutas rundorna med �terkoppling att datorn vann.
		{
			std::cout << "*********************" << std::endl;
			std::cout << "You have LOST the bet. " << endl;
			std::cout << "*********************" << std::endl;
			std::cout << "Your balance is now: " << balance << endl << endl;
			break;
		}
		else if (userScore == 2)// Om spelaren vann tv� rundor i rad, s� avslutas rundorna med �terkoppling att dem vann.
		{
			std::cout << "******CONGRATULATIONS!!******" << endl;
			std::cout << "You have WON the game!" << endl;
			balance = (betMoney * 2 + balance);
			std::cout << "Your account balance is now: " << balance << " kr" << endl << endl;
			&balance;
			break;
		}
	}
}
void exitGame() //Avslutar k�rningen/spelet.
{
	std::cout << "Game over" << endl;
	exit(1);
}