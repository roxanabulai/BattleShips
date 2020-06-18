#include "Player.h"

//constructor implicit
Player::Player()
{
	name = "";
	isAutomaticPlayer = false;
	playerNumber = 1;
}

//constructor cu param
Player::Player(std::string n, bool a, int num)
{
	name = n;
	isAutomaticPlayer = a;
	playerNumber = num;
}

// constructor de copiere
Player::Player(const Player& oldPlayer)
{
	name = oldPlayer.name;
	isAutomaticPlayer = oldPlayer.isAutomaticPlayer;
	playerNumber = oldPlayer.playerNumber;

}

//operator =
Player& Player::operator=(const Player& obj)
{
	if (this != &obj)
	{
		name = obj.name;
		isAutomaticPlayer = obj.isAutomaticPlayer;
		playerNumber = obj.playerNumber;
	}

	return *this;
}

//getteri
std::string Player::getName()
{
	return name;
}

int Player::getPlayerNumber()
{
	return playerNumber;
}

//verifica daca player ul e auto sau nu
bool Player::isPlayerAutomatic()
{
	return isAutomaticPlayer;
}



//setteri
void Player::setName(std::string n)
{
	name = n;
	return;
}

void Player::setAuto(bool a)
{
	isAutomaticPlayer = a;
	return;
}

void Player::setPlayerNumber(int n)
{
	playerNumber = n;
	return;
}