#include <iostream> 
#include <stdlib.h> 
#include <conio.h>
#include <windows.h> 
#include <string> 

#pragma once 

#ifndef CONSOLE_GAME 
#define CONSOLE_GAME 
enum Colour {
	BLACK = 0x0000,
	BLUE = 0x0001,
	GREEN = 0x0002,
	LBLUE = 0x0003,
	RED = 0x0004,
	PINK = 0x0005,
	YELLOW = 0x0006,
	WHITE = 0x0007,
	GREY = 0x0008,
	LRED = 0x000d,
	EMPTY = 0x1111
};

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void createPix(COORD pos, Colour col);

void createSquare(COORD lpos, COORD rpos, Colour col);

void createText(std::string text, COORD pos, Colour col);

void createShape(std::vector<std::vector<Colour>>& shape, COORD start);

void eraseShape(std::vector<std::vector<Colour>>& shape, COORD start);

#endif