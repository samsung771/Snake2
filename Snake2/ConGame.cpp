#include <iostream> 
#include <stdlib.h> 
#include <conio.h> 
#include <windows.h>
#include <string>
#include <vector> 
#include "ConGame.h" 

#define SQUARE 219 

void createPix(COORD pos, Colour col) {
	SetConsoleCursorPosition(hConsole, pos);
	SetConsoleTextAttribute(hConsole, col);
	std::cout << (char)SQUARE << (char)SQUARE;
}

void createSquare(COORD lpos, COORD rpos, Colour col) {
	SetConsoleTextAttribute(hConsole, col);
	for (int i = 0; i < rpos.Y - lpos.Y; i++) {
		SetConsoleCursorPosition(hConsole, COORD{ lpos.X,(short)(lpos.Y + i) });
		for (int j = 0; j < rpos.X - lpos.X; j++) {
			std::cout << (char)SQUARE << (char)SQUARE;
		}
	}
}

void createText(std::string text, COORD pos, Colour col) {
	SetConsoleTextAttribute(hConsole, col);
	SetConsoleCursorPosition(hConsole, pos);
	std::cout << text;
}

void createShape(std::vector<std::vector<Colour>>& shape, COORD start) {
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] != EMPTY) {
				createPix(COORD{ SHORT(start.X + (j * 2)), SHORT(start.Y + i) }, shape[i][j]);
			}
		}
	}
}

void eraseShape(std::vector<std::vector<Colour>>& shape, COORD start) {
	for (int i = 0; i < shape.size(); i++) {
		for (int j = 0; j < shape[0].size(); j++) {
			if (shape[i][j] != EMPTY) {
				createPix(COORD{ SHORT(start.X + (j * 2)), SHORT(start.Y + i) }, BLACK);
			}
		}
	}
}