#include "UI.h"
#include "Player.h"
#include <iostream>
#include <Windows.h>

int main()
{
	

	bool continueGame = true;
	
	UI ui;
	while (continueGame)
	{
		continueGame = ui.printMenu();
	}
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
	return 0;

}