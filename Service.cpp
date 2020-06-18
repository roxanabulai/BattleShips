#include "Service.h"
#include <iostream>


Service::Service()
{
	for (int i = 0; i < BOARD_DIM; i++)
		for (int j = 0; j < BOARD_DIM; j++)
			gameBoard[i][j] = isWATER; //nu exista vaporase momentan

	for (int i = 0; i < NUM_SHIPS; i++)
		vector_vaporase.push_back(Ship(SHIP_LENGTHS[i], SHIP_NAMES[i]));
}


Service::Service(const Service& s)
{
	for (int i = 0; i < BOARD_DIM; i++)
		for (int j = 0; j < BOARD_DIM; j++)
			gameBoard[i][j] = s.gameBoard[i][j];
	vector_vaporase = s.vector_vaporase;
}


Service& Service::operator=(const Service& s)
{
	if (this != &s)
	{
		for (int i = 0; i < BOARD_DIM; i++)
			for (int j = 0; j < BOARD_DIM; j++)
				gameBoard[i][j] = s.gameBoard[i][j];
		vector_vaporase = s.vector_vaporase;
	}

	return *this;

}


int Service::getNumHits()
{
	int count = 0;

	for (int i = 0; i < BOARD_DIM; i++)
		for (int j = 0; j < BOARD_DIM; j++)
			if (gameBoard[i][j] == isHIT)
				count++;

	return count;
}

// printarea tablei de joc private si doar jucatorul o poate vedea
void Service::printPrivateBoard()
{
	std::cout << "  A B C D E F G H I J\n";
	for (int i = 0; i < BOARD_DIM; i++)
	{
		std::cout << i << " ";
		for (int j = 0; j < BOARD_DIM; j++)
		{
			if (gameBoard[i][j] == isHIT || gameBoard[i][j] == isMISS)
				std::cout << gameBoard[i][j] << " ";
			else 
				std::cout << isUNKNOWN << " ";
		}
		std::cout << std::endl;
	}
}


void Service::printPublicBoard()
{
	std::cout << "  A B C D E F G H I J\n";
	for (int i = 0; i < BOARD_DIM; i++)
	{
		std::cout << i << " ";
		for (int j = 0; j < BOARD_DIM; j++)
		{
			std::cout << gameBoard[i][j] << " ";
		}
		std::cout << std::endl;
	}

}

//indica ce se afla in matrice la pozitia indicata de x,y
char Service::getSpaceValue(int x, int y)
{
	return gameBoard[y][x];
}

// record a hit on the board by attempting to record a hit on every ship
// if a ship is hit, change board position to hit and return true
// if no ship is hit, change board position to miss and return false
bool Service::recordHit(int x, int y)
{
	for (int i = 0; i < NUM_SHIPS; i++)
	{
		if (vector_vaporase[i].recordHit(x,y))
		{
			gameBoard[y][x] = isHIT; //record the hit on the board
			//tell the user that they sunk a ship
			if (vector_vaporase[i].isShipSunk())
				std::cout << "Ai scufundat un " << vector_vaporase[i].getName();
			return true;
		}
	}
	gameBoard[y][x] = isMISS;
	return false;
}

// function to place ship on board
bool Service::placeShip(int shipNum, int x, int y, bool isHorizontal)
{
	//daca s si y depasesc dimensiunile matricei
	if (x >= BOARD_DIM || y >= BOARD_DIM)
		return false;

	//exista deja o barca
	if (vector_vaporase[shipNum].getX() >= 0 && vector_vaporase[shipNum].getY() >= 0)
		return false;

	
	for (int i = 0; i < vector_vaporase[shipNum].getSize(); i++)
	{
		//daca exista deja un vaporas
		if ((isHorizontal && gameBoard[y][x + i] != isWATER) ||
			(!isHorizontal && gameBoard[y + i][x] != isWATER))
			return false;
		//daca depaseste dimensiunile matricei
		if ((isHorizontal && (x + i) >= BOARD_DIM) ||
			(!isHorizontal && (y + i) >= BOARD_DIM))
			return false;
	}


	//vaporasul este adaugat in matrice
	for (int i = 0; i < vector_vaporase[shipNum].getSize(); i++)
	{
		if (isHorizontal)
			gameBoard[y][x + i] = isSAFESHIP;
		else
			gameBoard[y + i][x] = isSAFESHIP;
	}

	
	vector_vaporase[shipNum].setPosition(x, y, isHorizontal);

	
	return true;
}