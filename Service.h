#pragma once
#include "Ship.h"
#include <vector>
#include "Constants.h"
using namespace std;

class Service
{
private:
	char gameBoard[BOARD_DIM][BOARD_DIM]; //matricea pe care se joaca
	std::vector<Ship> vector_vaporase;

public:
	Service(); // constructor implicit
	Service(const Service& oldBoard); //constructor cu param
	Service& operator=(const Service& ); //operator =
	~Service() { return; }; //destructor
	int getNumHits(); //numara vaporasele lovite

	void printPrivateBoard(); //printeaza tabla jucatorului
	void printPublicBoard(); //printeaza tabla computerului

	char getSpaceValue(int x, int y); 
	bool recordHit(int x, int y); 
	bool placeShip(int shipNum, int x, int y, bool isHorizontal); //verifica daca se poate realiza un vaporas in matrice

};