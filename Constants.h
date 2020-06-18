#pragma once
#include <string>

// game play constants (standard game of battleship)
const int NUM_SHIPS = 3;
const int BOARD_DIM = 10;
const int BOARD_SPACES = 100;
const int SHIP_LENGTHS[NUM_SHIPS] = { 5,3,2 };
const int TOTAL_SHIP_SPACES = 10;
const std::string SHIP_NAMES[NUM_SHIPS] = { "Vas de razboi","Yacht","Submarin" };


// board value constants
const char isHIT = 'X';
const char isMISS = 'O';
const char isWATER = 'w';
const char isSAFESHIP = '_';
const char isUNKNOWN = '?';

// to convert char to board position
const int LETTER_CHAR_OFFSET = 65;
const int NUMBER_CHAR_OFFSET = 48;

// consts for input validation
const int ASCII_INT_MIN = 48;
const int ASCII_INT_MAX = 57;


