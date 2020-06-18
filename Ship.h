#pragma once
#pragma once
#include <string>
using namespace std;
class Ship
{
private:
	char* shipSquares;
	int shipSize; //5, 3 sau 2
	int xpos, ypos; //ptr elem din matrice
	bool isSunk; //prt a putea spune daca e *aer* sau *atins*
	bool isHorizontal; // ptr a marca directia
	std::string name; 


public:
	Ship(int size, std::string n);//default constructor
	Ship(int size, std::string n, int x, int y, bool s, bool h);
	Ship(const Ship& oldShip); //constrcuctor de copiere
	
	//getteri
	int getSize() const;
	int getX() const;
	int getY() const;
	bool isShipSunk() const;
	bool isShipHorizontal() const;
	std::string getName() const;

	//setteri
	void setPosition(int x, int y, bool h);
	
	bool recordHit(int hitLocX, int hitLocY);

	//operator =
	Ship& operator=(const Ship& right);

	~Ship(); //destructor
};
