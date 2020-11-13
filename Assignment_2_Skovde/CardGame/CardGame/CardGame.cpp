/*
	@Author Elias Posluk
	@date 2016-01-07
	Kortspel
	H�gskolan i Sk�vde
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

//Prototyper
int menu();
int playNewGame(struct games*, struct cards*, int* cardOrd);
int name(games* game);
void newSuit(string playerName1, string playerName2, int playerScore1, int playerScore2);
void showScoreBoard(games* game);
void shuffleCards(cards* card, int* cardOrd);
void gameMenu(games* game, cards* player1Card, cards* player2Card, int nrOfDrawnCards);
void initDect(cards*);
void writeToFile(games* game);
void exitGame();

enum suit { //S�tter rankningen till korten, d�r clubs/kl�ver �r l�gsta och spades �r h�gsta
	clubs = 1,
	diamonds,
	hearts,
	spades,
};

enum value { //S�tter rankningen till korten, d�r Ess r�knas som den l�gsta kortet, och King �r h�gsta.
	Ace = 1,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King
};

struct player { // skapar variabler f�r spelarna, som ska anv�ndas under spelets g�ng.
	string name;
	int score = 0;
	int matchLoses = 0;
	int matchWins = 0;
};

struct games { //skapar tv� spelare
	player player1;
	player player2;
};

struct cards // 
{
	suit value;
	suit suit;
	int order; //ordningen i korten/decken
	bool used; // kollar om korten �r anv�nd eller ej.
	bool taken; // kollar om kortet �r tagen eller ej
};

int main() {
	cards dect[52]; // kort arrayen
	int dectOrder[52]; // int array med som h�ller koll p� ordningen p� korten.
	int choice = 0;
	string playerName1, playerName2;
	playerName1 = "default1";
	playerName2 = "default2";
	int player1Score = 0, player2Score = 0;
	games game;
	game.player1.name = playerName1;
	game.player1.score = player1Score;
	game.player2.name = playerName2;
	game.player2.score = player2Score;
	initDect(&dect[0]);
	name(&game);

	do {
		choice = menu();
		if (std::cin.good())
		{
			if (choice < 0)
			{
				std::string draw;
				std::cout << "You typed in an invalid option! Try again! " << endl; //Felmedellande om man trycker p� allt under siffran 1.
				std::cout << "Press any key to continue" << endl;
				std::cin >> draw;
			}
			else if (choice == 1)
			{
				playNewGame(&game, &dect[0], &dectOrder[0]); //kallelse till funktionen 'playNewGame', som k�r ig�ng spelet.
			}
			else if (choice == 2)
			{
				showScoreBoard(&game); //kallar till show score board 
			}
			else if (choice == 3)
			{
				writeToFile(&game);  //kallelse till funktionen 'readFromFile', som sparar spelarens information till textfil.
			}
			else if (choice == 4)
			{
				exitGame(); //kallar p� funktionen, som avslutar spelet.
			}
			else if (choice == 5)
			{
				//readFromFile(&game);
			}
			else if (choice > 5 || choice)
			{
				std::string draw;
				std::cout << "You typed in an invalid option! Try again! " << endl;//Felmedellande om man trycker p� siffran �ver 4.
				std::cout << "Press any key to continue" << endl;
				std::cin >> draw;
			}
		}
	} while (choice != 4);
	std::system("pause");
	return 0;
}

int menu() //Menun till spelet
{
	int choice = 0;
	bool bFail;
	do {
		std::system("cls");
		std::cout << "1. Play a game " << endl;
		std::cout << "2. Show my scoreboard " << endl;
		std::cout << "3. Save file" << endl;
		std::cout << "4. Exit game " << endl;
		//::cout << "5. Read from File " << endl;
		std::cin >> choice;
		bFail = cin.fail();
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //L�ter bli att krascha, efter felaktiga input.
	} while (bFail == true);
	return choice;
}

int name(games* game) {
	games* gamePtr;
	gamePtr = game;
	games test;

	std::cout << "Type in your names" << endl;
	std::cout << "Type in your name player1" << endl;
	std::getline(cin, gamePtr->player1.name); // f�r att kunna ta in namn med mellanslag
	std::cout << "Type in your name player2" << endl;
	std::getline(cin, gamePtr->player2.name);
	std::cout << endl;
	return 0;
}

int playNewGame(games* game, cards* card, int* cardOrd) {
	//	name(game);
	int nrOfDrawnCards = 0;
	games* gamePtr;
	gamePtr = game;
	cards* cardPtr;
	cards player1Card;
	cards player2Card;

	int index = 0;
	cardPtr = card;
	int* cardOrdPtr;
	cardOrdPtr = cardOrd;

	shuffleCards(card, cardOrd);
	gameMenu(game, nullptr, nullptr, nrOfDrawnCards);
	//Startar spelet med set 1
	for (int j = 1; j < 4; j++) {
		//kort 1
		nrOfDrawnCards++;
		index = *cardOrdPtr;
		player1Card = *(cardPtr + index);
		gameMenu(game, &player1Card, nullptr, nrOfDrawnCards);

		//Kort 2
		nrOfDrawnCards++;
		cardOrdPtr++;
		index = *cardOrdPtr;
		player2Card = *(cardPtr + index);
		gameMenu(game, &player1Card, &player2Card, nrOfDrawnCards);

		cardOrdPtr++;
	}
	if (gamePtr->player1.score > gamePtr->player2.score) // N�r man har k�rt en match,s� plusas vinnarens vinst i antal vunna matcher.
	{													// Samt s� plusas f�rlorarens f�rlorade matcher efter varje genomg�ngen match. 
		gamePtr->player1.matchWins++;					//Och s� nollst�lls b�gge spelarnas scores, efter varje match.
		gamePtr->player2.matchLoses++;
		gamePtr->player1.score = 0;
		gamePtr->player2.score = 0;
	}
	if (gamePtr->player1.score < gamePtr->player2.score)// Samma sak, fast f�r spelare 2.
	{
		gamePtr->player2.matchWins++;
		gamePtr->player1.matchLoses++;
		gamePtr->player1.score = 0;
		gamePtr->player2.score = 0;
	}
	return 0;
}

void gameMenu(games* game, cards* player1Card, cards* player2Card, int nrOfDrawnCards) { // H�r "spelas" spelet
	int drawnCards = nrOfDrawnCards;
	string draw;
	games* gamePtr;
	gamePtr = game;
	cards* cardPtr1;
	cardPtr1 = player1Card;
	cards* cardPtr2;
	cardPtr2 = player2Card;

	suit r;
	suit r2;
	system("cls");
	std::cout << "Total Points for this set" << endl; // skapar po�ngtabellen
	std::cout << "============" << endl;
	std::cout << gamePtr->player1.name << "\t" << gamePtr->player1.score << endl;
	std::cout << gamePtr->player2.name << "\t" << gamePtr->player2.score << endl;
	if (drawnCards == 0) { // N�r inga kort �r dragna
		std::cout << "============" << endl;
		std::cout << gamePtr->player1.name << "\t" << "\t" << "\t" << gamePtr->player2.name << endl;
		std::cout << "=========================================" << endl;
	}
	if ((drawnCards == 1) || (drawnCards == 3) || (drawnCards == 5)) { //N�r f�rsta spelarens kort �r dragen.
		std::cout << "============" << endl;
		std::cout << gamePtr->player1.name << "\t" << "\t" << "\t" << gamePtr->player2.name << endl;
		std::cout << "=========================================" << endl;
		r = cardPtr1->suit;
		switch (r) {
		case suit::clubs: std::cout << "Clubs\t"; break;
		case suit::diamonds: std::cout << "Diamonds\t"; break;
		case suit::hearts: std::cout << "Hearts\t"; break;
		case suit::spades: std::cout << "Spades\t"; break;
		}
		r2 = cardPtr1->value;
		switch (r2) {
		case value::Ace: std::cout << "Ace\t\t"; break;
		case value::Two: std::cout << "Two\t\t"; break;
		case value::Three: std::cout << "Three\t\t"; break;
		case value::Four: std::cout << "Four\t\t"; break;
		case value::Five: std::cout << "Five\t\t"; break;
		case value::Six: std::cout << "Six\t\t"; break;
		case value::Seven: std::cout << "Seven\t\t"; break;
		case value::Eight: std::cout << "Eight\t\t"; break;
		case value::Nine: std::cout << "Nine\t\t"; break;
		case value::Ten: std::cout << "Ten\t\t"; break;
		case value::Jack: std::cout << "Jack\t\t"; break;
		case value::Queen: std::cout << "Queen\t\t"; break;
		case value::King: std::cout << "King\t\t"; break;
		}
	}
	if ((drawnCards == 2) || (drawnCards == 4) || (drawnCards == 6)) { // N�r b�gge korten �r dragna
		std::cout << "============" << endl;
		std::cout << gamePtr->player1.name << "\t" << "\t" << "\t" << gamePtr->player2.name << endl;
		std::cout << "=========================================" << endl;
		r = cardPtr1->suit;
		switch (r) {
		case suit::clubs: std::cout << "Clubs\t"; break;
		case suit::diamonds: std::cout << "Diamonds\t"; break;
		case suit::hearts: std::cout << "Hearts\t"; break;
		case suit::spades: std::cout << "Spades\t"; break;
		}
		r2 = cardPtr1->value;
		switch (r2) {
		case value::Ace: std::cout << "Ace\t\t"; break;
		case value::Two: std::cout << "Two\t\t"; break;
		case value::Three: std::cout << "Three\t\t"; break;
		case value::Four: std::cout << "Four\t\t"; break;
		case value::Five: std::cout << "Five\t\t"; break;
		case value::Six: std::cout << "Six\t\t"; break;
		case value::Seven: std::cout << "Seven\t\t"; break;
		case value::Eight: std::cout << "Eight\t\t"; break;
		case value::Nine: std::cout << "Nine\t\t"; break;
		case value::Ten: std::cout << "Ten\t\t"; break;
		case value::Jack: std::cout << "Jack\t\t"; break;
		case value::Queen: std::cout << "Queen\t\t"; break;
		case value::King: std::cout << "King\t\t"; break;
		}
		r = cardPtr2->suit;
		switch (r) {
		case suit::clubs: std::cout << "Clubs\t"; break;
		case suit::diamonds: std::cout << "Diamonds\t"; break;
		case suit::hearts: std::cout << "Hearts\t"; break;
		case suit::spades: std::cout << "Spades\t"; break;
		}
		r2 = cardPtr2->value;
		switch (r2) {
		case value::Ace: std::cout << "Ace\n"; break;
		case value::Two: std::cout << "Two\n"; break;
		case value::Three: std::cout << "Three\n"; break;
		case value::Four: std::cout << "Four\n"; break;
		case value::Five: std::cout << "Five\n"; break;
		case value::Six: std::cout << "Six\n"; break;
		case value::Seven: std::cout << "Seven\n"; break;
		case value::Eight: std::cout << "Eight\n"; break;
		case value::Nine: std::cout << "Nine\n"; break;
		case value::Ten: std::cout << "Ten\n"; break;
		case value::Jack: std::cout << "Jack\n"; break;
		case value::Queen: std::cout << "Queen\n"; break;
		case value::King: std::cout << "King\n"; break;
		}
		//std::cout << cardPtr2->value << endl;
		std::cout << endl;
		//std::cout << cardPtr1->value << endl;
		std::cout << "Press any key for the result" << endl;
		std::cin >> draw;

		if (cardPtr1->value > cardPtr2->value) {
			gamePtr->player1.score++;
			std::cout << gamePtr->player1.name << " Won" "\t" "New Score is:" << "\t" << gamePtr->player1.score << " " "-" << " " << gamePtr->player2.score << endl;
		}
		if (cardPtr1->value < cardPtr2->value) {
			gamePtr->player2.score++;
			std::cout << gamePtr->player2.name << " Won" "\t" "New Score is" << "\t" << gamePtr->player1.score << " " "-" << " " << gamePtr->player2.score << endl;
		}
		if (cardPtr1->value == cardPtr2->value) {
			if (cardPtr1->suit > cardPtr2->suit) {
				gamePtr->player1.score++;
				std::cout << gamePtr->player1.name << " Won" "\t" "New Score is" << "\t" << gamePtr->player1.score << " " "-" << " " << gamePtr->player2.score << endl;
			}
			else {
				gamePtr->player2.score++;
				std::cout << gamePtr->player2.name << " Won" "\t" "New Score is" << "\t" << gamePtr->player1.score << " " "-" << " " << gamePtr->player2.score << endl;
			}
		}
	}

	std::cout << endl;

	if (drawnCards == 6) {
		if (gamePtr->player1.score > gamePtr->player2.score) {
			std::system("cls");
			std::cout << endl;
			std::cout << endl;
			std::cout << endl;
			std::cout << endl;
			std::cout << "#############################################################";
			std::cout << endl;
			std::cout << gamePtr->player1.name << " " << "Won the Match!" << std::endl;
			std::cout << "#############################################################";
			std::cout << endl;

		}
		else
		{
			std::system("cls");
			std::cout << endl;
			std::cout << endl;
			std::cout << endl;
			std::cout << endl;
			std::cout << "#############################################################";
			std::cout << endl;
			std::cout << gamePtr->player2.name << " " << "Won the Match!" << std::endl;
			std::cout << "#############################################################";
			std::cout << endl;
		}

	}

	std::cout << endl;
	std::cout << endl;
	std::cout << endl;
	std::cout << endl;

	std::cout << "Press any key to continue" << endl;
	std::cin >> draw;

}

void shuffleCards(cards* card, int* cardOrd) { //Blandar korten, innan utdelning.
	int* deckPtr;
	deckPtr = cardOrd;
	cards* card1;
	card1 = card;

	srand((int)time(NULL));

	bool ok = false;
	int numb;
	for (int i = 1; i <= 52; i++) {
		card1->taken = false;
		card1++;
	}
	card1 = card;
	for (int i = 1; i <= 52; i++) {
		ok = false;
		while (ok == false) {
			numb = rand() % 52;
			if ((card1 + numb)->taken == false) {
				(card1 + numb)->taken = true;
				(card1 + numb)->order = i;
				*deckPtr = numb;
				deckPtr++;
				ok = true;
			}
		}
	}

	card1 = card;
	deckPtr = cardOrd;
}

void showScoreBoard(games* game) { // Visar antalet vunna matcher, efter att man har spelat ett x antal rundor.
	string draw;
	games* gamePtr;
	gamePtr = game;
	std::cout << gamePtr->player1.name << ":";
	std::cout << "=========================" << endl;
	std::cout << "Number of won matches" << "=" << gamePtr->player1.matchWins << endl;
	std::cout << "Number of lost matches" << "=" << gamePtr->player1.matchLoses << endl << endl;
	std::cout << gamePtr->player2.name << ":";
	std::cout << "=========================" << endl;
	std::cout << "Number of won matches" << "=" << gamePtr->player2.matchWins << endl;
	std::cout << "Number of lost matches" << "=" << gamePtr->player2.matchLoses << endl;

	std::cout << "Press any key to continue" << endl;
	std::cin >> draw;
}

void initDect(cards* card) { //Skapar kortleken i arrayen, spader, hj�rter, rutor, kl�ver
	cards *card1;
	card1 = card;
	for (int i = 1; i <= 13; i++) { // spader
		card1->value = (suit)i;
		card1->suit = spades;
		card1->used = false;
		card1->order = i;
		card1->taken = false;
		card1++;
	}
	for (int i = 14; i <= 26; i++) {
		card1->value = (suit)(i - 13);
		card1->suit = hearts;
		card1->used = false;
		card1->order = i;
		card1->taken = false;
		card1++;
	}
	for (int i = 27; i <= 39; i++) {
		card1->value = (suit)(i - 26);
		card1->suit = diamonds;
		card1->used = false;
		card1->order = i;
		card1->taken = false;
		card1++;
	}
	for (int i = 40; i <= 52; i++) {
		card1->value = (suit)(i - 39);
		card1->suit = clubs;
		card1->used = false;
		card1->order = i;
		card1->taken = false;
		card1++;
	}
}

void writeToFile(games* game)//Funktionen som sparar ner information om spelaren.
{
	string draw;
	games* gamePtr;
	gamePtr = game;

	ofstream outFile;
	outFile.open("CardGame.txt"); //Textdokumentet som informationen kommer sparas till heter "CardGame.txt" 
	outFile << "Player " << gamePtr->player1.name << " got: " << gamePtr->player1.matchWins << " match wins. " << std::endl << std::endl; //Visar spelarens namn samt hur m�nga matcher man har vunnit samt f�rlorat.
	outFile << "Player " << gamePtr->player1.name << " got: " << gamePtr->player1.matchLoses << " match loss." << std::endl << std::endl;
	outFile << "Player " << gamePtr->player2.name << " got: " << gamePtr->player2.matchWins << " match wins. " << std::endl << std::endl; //Visar spelare tv�s namn samt hur m�nga matcher man har vunnit samt f�rlorat.
	outFile << "Player " << gamePtr->player2.name << " got: " << gamePtr->player2.matchLoses << " match loss." << std::endl << std::endl;
	outFile.close();
	std::cout << "Your information is saved to file!" << endl; //Ger �terkoppling till spelaren, att informationen har sparats.
	std::cout << "Press any key to continue" << endl;

	std::cin >> draw;
}

void exitGame() { // trycker spelaren p� nr.4 i menyn, s� st�ngs programmet av.
	std::cout << "Game over" << endl;
	system("pause");
	exit(1);
}