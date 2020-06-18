#pragma once
#include <string>

class Player
{
private:
	std::string name;
	bool isAutomaticPlayer; //verifica daca player ul este auto
	int playerNumber;
public:
	Player(); //constr implicit
	Player(std::string n, bool a, int num); //constructor cu parametri
	Player(const Player& oldPlayer); //constr de copiere

	Player& operator=(const Player& obj); //operator =

	~Player() { return; }; //destructor

	//getteri
	std::string getName();
	int getPlayerNumber();
	
	//verifica daca player ul e auto
	bool isPlayerAutomatic();
	
	//setteri
	void setName(std::string n);
	void setAuto(bool a);
	void setPlayerNumber(int n);
};
