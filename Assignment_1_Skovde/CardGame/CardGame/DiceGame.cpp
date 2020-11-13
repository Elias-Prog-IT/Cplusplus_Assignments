/*
	@Author Elias Posluk
	Student-id: elpo14
	@date 2015-10-07
	Tärningsspel
	Högskolan i Skövde
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

	srand((unsigned int)time(NULL));// fick varning när jag hade srand()(time(0)), så jag gjorde lite google sökning och fick fram att man ska ha "unsigned int" för att få bort varningen. 

	//Välkomstmeddelande, och förfrågar namnet på spelaren.
	std::cout << "***************************************" << endl;
	std::cout << " ******* " << " Welcome to the dice game! " << " *******" << endl;
	std::cout << "***************************************" << endl;
	std::cout << "What's your name?" << endl;
	cin >> name;
	do																	//Do-while loop som loopar igång menyn till spelet. Menyn innehåller 4 val. Samt felmedellande om man väljer val som inte finns i menyn.
	{
		choice = menu();
		if (cin.good())
		{
			if (choice < 0)
			{
				std::cout << "You typed in an invalid option! Try again! " << endl; //Felmedellande om man trycker på allt under siffran 1.
			}
			else if (choice == 1)
			{
				playNewGame(name, balance, betMoney, deposit, userScore, pcScore); //kallelse till funktionen 'playNewGame', som kör igång spelet.
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
				exitGame(); //kallar på funktionen, som avslutar spelet.
			}
			else if (choice > 4)
			{
				std::cout << "You typed in an invalid option! Try again! " << endl;//Felmedellande om man trycker på siffran över 4.
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
	outFile << "User " << name << " got the amount " << balance << " kr" << std::endl; //Visar spelarens namn samt hur mycket man har på kontot.
	outFile.close();
	std::cout << "Your information is saved!" << endl; //Ger återkoppling till spelarn att informationen har sparats.
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

	std::cout << "Welcome " << name << " ! " << std::endl; //Kör man igång spelet, så möts man med en hälsning samt påminelse på hur mycket man har i kontot. 
	std::cout << "Your account  balance is " << balance << " kr" << std::endl;
	std::cout << std::endl;

	if (balance <= 0) //Om man inte har pengar i kontot, dvs har 0kr, så hamnar man här, där spelaren får sätta in pengar.
	{
		std::cout << "You unfortunately don't have enough money in your account. " << std::endl;
		std::cout << "How much money do you want to deposit? " << std::endl;
		cin >> deposit;
		if (deposit == 100 || deposit == 300 || deposit == 500) // Kollar om spelaren sätter in rätt mängd pengar som man får sätta in. 
		{
			std::cout << "Your amount to deposit is admited" << std::endl; // Får återkoppling att ens insättning har gått bra till.
			std::cout << (balance = (balance + deposit)) << std::endl;
		}
		else if (deposit != 100 || deposit != 300 || deposit != 500) //Om man inte sätter in rätt mängd, så får man felmedellande där man får återkoppling om vad som gick fel, samt att kunna göra om det igen.
		{
			std::cout << "The entered amount is not an accepted value! " << std::endl;
			std::cout << "Please make a new bet with the amount of either 100kr, 300kr, or 500kr" << std::endl;
			std::cin >> deposit;
			balance = (balance + deposit);
		}
	}
	else if (balance > 0) // Om man har kört en omgång innan och kör omspelet, så hamnar man här, om man fortfarande har pengar i kontot. Då blir man tillfrågad om man vill sätta in mer pengar i kontot. 
	{							//Svarar man med 'y' eller 'Y', så går man in i  if-satsen där man får sätta in pengar. Annars om man väljer 'n' eller 'N' så hamnar man direkt på bettningen.
		std::cout << "Do you want to do an extra deposit to your account?  (y/n)" << std::endl;
		cin >> change;
		if (change == 'y' || change == 'Y')
		{
			std::cout << "How much money do you want to deposit? " << std::endl;
			cin >> deposit;
			if (deposit + balance < maxAmount)
			{
				if (deposit == 100 || deposit == 300 || deposit == 500) // Kollar om spelaren sätter in rätt mängd pengar som man får sätta in. 
				{
					std::cout << "Your amount to deposit is admited" << std::endl;
					std::cout << (balance = (balance + deposit)) << std::endl;
				}
				else if (deposit != 100 || deposit != 300 || deposit != 500)  //Om man inte sätter in rätt mängd, så får man felmedellande där man får återkoppling om vad som gick fel, samt att kunna göra om det igen.
				{
					std::cout << "The entered amount is not an accepted value! " << std::endl;
					std::cout << "Please make a new bet with the amount of either 100kr, 300kr, or 500kr" << std::endl;
					std::cin >> deposit;
					balance = (balance + deposit);
				}
			}
			else if (maxAmount < balance + deposit) // Här kommer spärren på 5000kr, if-satsen kollar på hur mycket du har i kontot, samt hur mycket du vill sätta in i kontot igen inte överstiger maxsumman på kontot.
			{
				std::cout << "Sorry, but you can  only have 5000kr in your account. " << std::endl;
				std::cout << " Your account balance now: " << balance << " kr" << std::endl;
			}
		}
	}
	std::cout << "How much money do you want to bet? " << endl;
	cin >> betMoney;
	if (betMoney == 100 || betMoney == 300 || betMoney == 500)//Checkar av så att man bettar rätt mängd som är tillåtet
	{
		std::cout << "Your bet is admited" << endl;
		balance = (balance - betMoney);
	}
	else if (betMoney != 100 || betMoney != 300 || betMoney != 500) // Blir en återkoppling som påmminer om hur mycket man får betta, om man bettar fel summa.
	{
		std::cout << "The entered amount is not an accepted value! " << endl;
		std::cout << "Please make a new bet with the amount of either 100kr, 300kr, or 500kr" << endl;
		cin >> betMoney;
		balance = (balance - betMoney);
	}
	cout << "You betted :" << betMoney << endl;
	std::cout << "Your account balance is now " << balance << endl;
	cout << "Press enter to start rolling your dices' " << endl; //För att påbörja dicespelet krävs att man trycker på enter
	getchar();
	getchar();
	int i = 0;
	userScore = 0;
	pcScore = 0;
	while (i < 3) // Loopar igenom tärningskasten max tre gånger.
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

		if (firstDice > secondDice) //om spelarens första tärning är större än den andra tärningen.
		{
			userDie1 = firstDice; //Så hamnar tärningens summa i variabeln userDie1
		}
		else
		{
			userDie1 = secondDice; //Annars är spelarens andra tärning större än spelarens första tärning, och den summan hamnar i variabeln userDie1.
		}
		if (thirdDice > fourthDice)//Här kollar vi om datorns första tärning är större än den andra tärningen.
		{
			pcDie1 = thirdDice;//Är datorns första tärning större än andra tärningen, så hamnar datan/summan i variabeln pcDie1.
		}
		else
		{
			pcDie1 = fourthDice;//Om datorns andra tärning är större, så hamnar summan i pcDie1 istället.
		}
		if (userDie1 > pcDie1) //Om spelaren har en högre siffra, så vinner dem rundan
		{
			std::cout << "You have won the round! " << endl;
			userScore++;
		}
		else if (pcDie1 > userDie1)// datorn vinner rundan om dem har högre siffra
		{
			std::cout << "You have lost the round! " << endl;
			pcScore++;
		}
		else //om bägge spelaren och datorn har likadana siffror, så blir det oavgjort, där datorn får poäng.
		{
			std::cout << "*********************" << std::endl;
			std::cout << "It's a TIE! " << endl;
			std::cout << "*********************" << std::endl;
			pcScore++;
		}
		std::cout << "The score is: " << name << ": " << userScore << " " << "computer: " << pcScore << endl << endl; // Återkoppling på hur många poäng man har efter rundorna
		if (pcScore == 2) //Om datorn har vunnit två rundor i rad, så avslutas rundorna med återkoppling att datorn vann.
		{
			std::cout << "*********************" << std::endl;
			std::cout << "You have LOST the bet. " << endl;
			std::cout << "*********************" << std::endl;
			std::cout << "Your balance is now: " << balance << endl << endl;
			break;
		}
		else if (userScore == 2)// Om spelaren vann två rundor i rad, så avslutas rundorna med återkoppling att dem vann.
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
void exitGame() //Avslutar körningen/spelet.
{
	std::cout << "Game over" << endl;
	exit(1);
}