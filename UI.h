#pragma once
#include "Service.h"
#include "Player.h"

enum state { P1_WIN, P2_WIN, UNFINISHED };

class UI
{
private:
	Player p1;
	Service p1Board;
	Player p2;
	Service p2Board;
public:
	//bool recordHit_UI(int x, int y);
	bool playGame();
	void startGame();
	//initializare ptr cele 2 table de joc
	void initializeBoard(Service& b);
	void initializeBoardAuto(Service& b, bool print = true);

	state gameCondition(); //indica daca jocul s-a terminat

	void printGameState(Player p);

	void getNextMove(Service& b);
	void getNextMoveAuto(Service& b);
	std::string getSquare();
	void switchPlayers(std::string playerFrom, std::string playerTo);

	bool printMenu();

	//void printPrivateBoard(); //printeaza tabla jucatorului
	//void printPublicBoard(); //printeaza tabla computerului
};

