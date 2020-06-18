#include "UI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "RepoException.h"

// function to play game
bool UI::playGame()
{
	int firstPlayer, currentPlayer, toPlay;
	Service* bptr;
	Player* pptr;

	startGame();
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	std::cout << "Care player face prima miscare (introduceti 1 sau 2)?\n";
	//int opt;
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	cin >> firstPlayer;


	// hold pointers for current player/board objects
	if (firstPlayer != 1 and firstPlayer != 2)
	{
		throw RepoException("Trebuie sa alegeti 1 sau 2");
	}
	else if (firstPlayer == 1)
	{
		pptr = &p1;
		bptr = &p2Board;
	}
	else {
		pptr = &p2;
		bptr = &p1Board;
	}

	while (gameCondition() == UNFINISHED) //daca jocul inca nu s-a terminat
	{
		if ((*pptr).isPlayerAutomatic())
		{
			getNextMoveAuto(*(bptr));
		}
		else
		{
			//printGameState(*(pptr));
			getNextMove(*(bptr));
			printGameState(*(pptr));
		}
		

		// switch pointers at the end of each turn
		if ((*pptr).getPlayerNumber() == 1)
		{
			if (!p1.isPlayerAutomatic() && !p2.isPlayerAutomatic())
			{
				switchPlayers(p1.getName(), p2.getName());
			}
			pptr = &p2;
			bptr = &p1Board;
		}
		else {
			if (!p1.isPlayerAutomatic() && !p2.isPlayerAutomatic())
			{
				switchPlayers(p2.getName(), p1.getName());
			}
			pptr = &p1;
			bptr = &p2Board;
		}
	}
	cout << endl;
	SetConsoleTextAttribute(h, FOREGROUND_RED);
	if (gameCondition() == P1_WIN)
		std::cout << p1.getName() << " wins!!!" << std::endl;
	else
		std::cout << p2.getName() << " wins!!!" << std::endl;

	SetConsoleTextAttribute(h, FOREGROUND_RED);
	std::cout << "I hope you enjoyed the Battleship game. Bye!\n\n";
	return true;

}

// function to perform necessary setup before game is played
void UI::startGame()
{
	std::string name;
	int autom;

	//set player numbers
	p1.setPlayerNumber(1);
	p2.setPlayerNumber(2);
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	//get player names
	std::cout << "Care este numele dumneavoastra (<=32 chars)?\n";
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	cin >> name;
	p1.setName(name);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	std::cout << "Bine ati venit, " << p1.getName() << "!" << std::endl;

	//std::cout << "Care este numele celui de-al doilea jucator (<=32 chars)?\n";
	//p2.setName(getString(32));
	//std::cout << "Welcome, " << p2.getName() << "!" << std::endl;

	//get automatic statuses
	//std::cout << "Ce tip de player este " << p1.getName()
		//<< "? (introduceti 0 pentru non-auto, 1 pentru auto)\n";
	p1.setAuto(false);
	p2.setAuto(true);
	//p1.setAuto(getInt(0, 1));

	//std::cout << "Ce tip de player este " << p2.getName()
		//<< "? (introduceti 0 pentru non-auto, 1 pentru auto)\n";
	//p2.setAuto(getInt(0, 1));


	//initialize both boards, according to whether the players are automatic
	//if (p1.isPlayerAutomatic())
		//initializeBoardAuto(p1Board, false);
	//else
	//{
		//std::cout << p1.getName() << ", cum preferi BattleField ul sa fie setat?"
			//<< " (introduceti 0 pentru non-auto, 1 pentru auto)\n";
		//autoTemp = getInt(0, 1);
		//if (autoTemp)
			//initializeBoardAuto(p1Board, true);
		//else initializeBoard(p1Board);

//	}

	// if both players are non-auto, clear screen appropriately between fills
	/*if (!p2.isPlayerAutomatic() && !p1.isPlayerAutomatic())
	{
		switchPlayers(p1.getName(), p2.getName());
	}
	*/
	//initializeBoard(p1Board);
	//initializeBoardAuto(p2Board, true);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	std::cout << p1.getName() << ", cum preferi BattleField ul sa fie setat?"
			<< " (introduceti 0 pentru non-auto, 1 pentru auto)\n";
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	int opt;
	cin >> opt;
	//autom = getInt(0, 1);
	if (opt==1)
			initializeBoardAuto(p1Board, true);
	else initializeBoard(p1Board);

	initializeBoardAuto(p2Board,false);
	/*if (!p2.isPlayerAutomatic() && !p1.isPlayerAutomatic())
	{
		std::cout << std::string(100, '\n');
	}
	*/
	return;
}

// prints game state, with player's own board exposed and opponent's board
// mostly obscured, save for moves player has made
void UI::printGameState(Player p)
{
	std::cout << p.getName() << "'s GAME STATE:\n\n";
	if (p.getPlayerNumber() == 1)
	{
		HANDLE g = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(g, FOREGROUND_RED);
		std::cout << "YOUR BOARD: \n";
		p1Board.printPublicBoard();
		SetConsoleTextAttribute(g, FOREGROUND_BLUE);
		std::cout << "YOUR OPPONENT'S BOARD: \n";
		p2Board.printPrivateBoard();
		//std::cout << std::endl << std::endl;
	}
	else
	{
		HANDLE g = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(g, FOREGROUND_RED);
		std::cout << "YOUR BOARD: \n";
		p2Board.printPublicBoard();
		SetConsoleTextAttribute(g, FOREGROUND_BLUE);
		std::cout << "YOUR OPPONENT'S BOARD: \n";
		p1Board.printPrivateBoard();
		//std::cout << std::endl << std::endl;
	}


	return;
}

// initializes board based on user input 
void UI::initializeBoard(Service& b)
{
	int xEntry, yEntry, horizEntry, attemptCount;
	std::string entryTemp;
	for (int i = 0; i < NUM_SHIPS; i++)
	{
		attemptCount = 0;
		do // check for valid placement of each ship
		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, FOREGROUND_GREEN);
			b.printPublicBoard();
			if (attemptCount > 0)
				std::cout << "INVALID ENTRY for that ship! Please try again. \n";

			std::cout << "Te rog sa introduci locatia [Letter][Number] pentru " << SHIP_NAMES[i] << " care are lungimea "
				<< SHIP_LENGTHS[i] << ": \n";
			SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
			entryTemp = getSquare();
			xEntry = static_cast<int>(entryTemp[0]);
			yEntry = static_cast<int>(entryTemp[1]);

			SetConsoleTextAttribute(h, FOREGROUND_GREEN);
			std::cout << "introduceti 0 daca vaporasul este orientat vertical, "
				<< "1 daca este orientat orizontal:\n";
			int opt;
			SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
			cin >> opt;
			horizEntry = opt;

			attemptCount++;
		} while (!b.placeShip(i, xEntry - LETTER_CHAR_OFFSET,
			yEntry - NUMBER_CHAR_OFFSET, horizEntry));

	}
	HANDLE g = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(g, FOREGROUND_RED);
	std::cout << "Your starting board: \n";
	b.printPublicBoard();

	return;
}


// initializes a board with random placement of ships on a board 
void UI::initializeBoardAuto(Service& b, bool print)
{
	int xEntry, yEntry, horizEntry;

	for (int i = 0; i < NUM_SHIPS; i++)
	{
		do // randomize position placements and place ships if possible
		{
			xEntry = rand() % 10;
			yEntry = rand() % 10;
			horizEntry = rand() % 2;
		} while (!b.placeShip(i, xEntry, yEntry, horizEntry));

	}

	if (print)
	{
		HANDLE g = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(g, FOREGROUND_RED);
		std::cout << "Your starting board: \n";
		b.printPublicBoard();
	}


	return;
}

// returns enum determining state of game
state UI::gameCondition()
{
	if (p1Board.getNumHits() == TOTAL_SHIP_SPACES)
		return P2_WIN;

	else if (p2Board.getNumHits() == TOTAL_SHIP_SPACES)
		return P1_WIN;

	else
		return UNFINISHED;
}


// function to prompt a player to actively choose which move to make 
void UI::getNextMove(Service& b)
{
	int attemptCount = 0;
	int xEntry, yEntry;
	bool goodMove = false;
	std::string entryTemp;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	while (!goodMove)
	{
		if (attemptCount > 0)
			std::cout << "Ups! Aceasta miscare a mai fost executata. Try again. \n";

		std::cout << "Te rog sa introduci locatia [Letter][Number] miscarii dorite:\n";
		entryTemp = getSquare();
		xEntry = static_cast<int>(entryTemp[0]);
		yEntry = static_cast<int>(entryTemp[1]);

		if (b.getSpaceValue(xEntry - LETTER_CHAR_OFFSET,
			yEntry - NUMBER_CHAR_OFFSET) != isHIT
			&& b.getSpaceValue(xEntry - LETTER_CHAR_OFFSET,
				yEntry - NUMBER_CHAR_OFFSET) != isMISS)
		{

			b.recordHit(xEntry - LETTER_CHAR_OFFSET, yEntry - NUMBER_CHAR_OFFSET);
			cout << endl;
			cout << "LOVIT" << endl;
			goodMove = true;
		}
		else { cout << "AER" << endl; }
		attemptCount++;
	}

	return;
}


// function to make a random move
void UI::getNextMoveAuto(Service& b)
{
	bool adauga = false;
	int x, y;

	while (!adauga)
	{
		// randomly choose next move
		x = rand() % 10;
		y = rand() % 10;

		if (b.getSpaceValue(x, y) != isHIT
			&& b.getSpaceValue(x, y) != isMISS) //daca locul ales nu a fost lovit sau nu e gol
		{
			
			b.recordHit(x, y);
			adauga = true;
		}
	}
	return;
}

// input validation for square
std::string UI::getSquare()
{
	std::string retString;
	std::getline(std::cin, retString);
	bool isGoodInput = false;

	while (!isGoodInput)
	{
		// check for two character entries of letter/number
		if (retString.length() == 2 && (retString[0] >= 65 && retString[0] <= 74)
			&& (retString[1] >= 48 && retString[1] <= 57))
			isGoodInput = true;
		else
		{
			std::cout << "UPS! Te rog sa introduci locatia [Letter][Number] miscarii dorite "
				<< "doar cu litere mari:\n";
			std::getline(std::cin, retString);
		}
	}

	return retString;
}


void UI::switchPlayers(std::string playerFrom, std::string playerTo)
{
	std::cout << playerFrom << ", press ENTER to finish your turn!";
	std::cin.get();
	std::cout << std::flush;
	std::cout << std::string(100, '\n');
	std::cout << playerTo << ", press ENTER to start your turn!";
	std::cin.get();
	std::cout << std::flush;
	std::cout << std::string(100, '\n');

}


bool UI:: printMenu()
{
	
	int cont;
	HANDLE g = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(g, FOREGROUND_GREEN);
	std::cout << "Welcome to Battleship! Introduceti 1 sau 2 pentru: \n1. A incepe un joc nou."
		<< "\n2. A iesi.\n\n";
	int opt;
	cin >> opt;
	//cont = getInt(1, 2);

	if (opt == 1)
	{
		this->playGame();
		return true;
	}
	else {
		SetConsoleTextAttribute(g, FOREGROUND_RED);
		std::cout << "La revedere!";
		return false;
	}

}