#include "Ship.h"
#include "Constants.h"
#include <iostream>

using std::cout;


Ship::Ship(int size, std::string n)
{
	shipSize = size;
	name = n;
	shipSquares = new char[shipSize];

	for (int i = 0; i < shipSize; i++)
		shipSquares[i] = isSAFESHIP; //initializez toate patratelele cu "-"
		
	xpos = -1;
	ypos = -1;
	isSunk = false;
	isHorizontal = true;
}

//constructor cu parametri
Ship::Ship(int size, std::string n, int x, int y, bool s, bool h)
{
	shipSize = size;
	name = n;
	shipSquares = new char[shipSize];
	for (int i = 0; i < shipSize; i++)
		shipSquares[i] = isSAFESHIP;
	xpos = x;
	ypos = y;
	isSunk = s;
	isHorizontal = h;
}


// constructor de copiere
Ship::Ship(const Ship& oldShip)
{
	shipSize = oldShip.getSize();
	name = oldShip.getName();
	shipSquares = new char[shipSize];
	for (int i = 0; i < shipSize; i++)
		shipSquares[i] = oldShip.shipSquares[i];
	xpos = oldShip.getX();
	ypos = oldShip.getY();
	isSunk = oldShip.isShipSunk();
	isHorizontal = oldShip.isShipHorizontal();
}

Ship& Ship::operator=(const Ship& right)
{
	if (this != &right)
	{
		shipSize = right.getSize();
		name = right.getName();
		xpos = right.getX();
		ypos = right.getY();
		isSunk = right.isShipSunk();
		isHorizontal = right.isShipHorizontal();

		if (shipSize > 0)
			delete[] shipSquares;
		shipSquares = new char[shipSize];
		for (int i = 0; i < shipSize; i++)
			shipSquares[i] = right.shipSquares[i];


	}
	return *this;

}

// destrcuctor
Ship::~Ship()
{
	if (shipSize > 0)
		delete[] shipSquares;
}

// getteri
int Ship::getSize() const
{
	return shipSize;
}

int Ship::getX() const
{
	return xpos;
}

int Ship::getY() const
{
	return ypos;
}

bool Ship::isShipSunk() const
{
	return isSunk;
}

bool Ship::isShipHorizontal() const
{
	return isHorizontal;
}

std::string Ship::getName() const
{
	return name;
}

// set position
void Ship::setPosition(int x, int y, bool h)
{
	xpos = x;
	ypos = y;
	isHorizontal = h;
	return;
}

// function to record hit on ship, return false if no hit, true if hit
// Note: hitLocX = loc on lettered axis, hitLocY = loc on numbered axis
bool Ship::recordHit(int hitLocX, int hitLocY)
{
	//verifica daca a fost lovit vaporasul
	if ((isHorizontal & (hitLocX < xpos || hitLocX >= xpos + shipSize
		|| hitLocY != ypos))
		|| (!isHorizontal & (hitLocY < ypos || hitLocY >= ypos + shipSize
			|| hitLocX != xpos)))
		return false; //ret false deoarece nu a fost lovit
	else // if there is a hit, record it on the ship
	{
		if (isHorizontal)
			shipSquares[hitLocX - xpos] = isHIT;
		else
			shipSquares[hitLocY - ypos] = isHIT;
	}

	//determine whether the ship has been sunk
	isSunk = true;
	for (int i = 0; i < shipSize; i++)
		if (shipSquares[i] == isSAFESHIP)
			isSunk = false;

	return true;
}