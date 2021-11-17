#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <vector>
#include <cmath>
#include <string>
#include <climits>
#include "ConGame.h"

//dimensions
#define DIMX 20
#define DIMY 20

//colour schemes
#define SNAKEHEAD  YELLOW
#define SNAKEBODY  GREEN
#define WALLCOL    WHITE
#define ENVIROCOL  BLACK
#define FRUITCOL   RED

class Game {
private:
	//init variables
	enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
	bool gameOver = false;
	const COORD dimensions = { DIMX,DIMY };
	COORD headPos = { 1,1 };
	COORD fruitPos = { 1,1 };

	std::chrono::steady_clock::time_point lastMove;
	std::chrono::steady_clock::time_point curTime;

	std::vector<COORD> snake;

	int score;
	int len = 2;
	int moveTime = 70 * pow((1 / 1.25), len - 2) + 80;

	Direction dir = STOP;
	Direction temp = STOP;

	//init function
	void Setup() {
		//assigns all variables
		len = 2; moveTime = 70 * pow((1 / 1.25), len - 2) + 80; //resets snake 
		snake.clear();
		lastMove = std::chrono::steady_clock::now();
		srand(time(NULL));
		gameOver = false;
		dir = STOP; score = 0;
		headPos = { (short)(dimensions.X / 2),(short)(dimensions.Y / 2) }; //updates screen 
		DrawEnviro();
		updateScore();
	}

	void DrawEnviro() {
		//clears screen 
		system("cls");
		//creates board 
		createSquare(COORD{ 0,0 }, COORD{ (short)(dimensions.X + 2),(short)(dimensions.Y + 2) }, WALLCOL);
		createSquare(COORD{ 2,1 }, COORD{ (short)(dimensions.X + 2),(short)(dimensions.Y + 1) }, ENVIROCOL);
		updateFruit();
	}

	void updateScore() {
		createText(std::to_string(score),
			COORD{ (short)(dimensions.X + 2 - (std::to_string(score).length() - 1) / 2),
			(short)(dimensions.Y + 2) }, WHITE);
	}

	void updateFruit() {
		//new random fruit pos 
		fruitPos = { (short)(rand() % (dimensions.X - 1) + 1),(short)(rand() % (dimensions.Y - 1) + 1) };
		//loops through until fruit doesn't spawn in the snake 
		for (COORD i : snake) if (i.X == fruitPos.X && i.Y == fruitPos.Y) updateFruit();
		//updates fruit if it spawns in the snakes head 
		if (headPos.X == fruitPos.X && headPos.Y == fruitPos.Y) updateFruit();
		//prints fruit 
		createPix(COORD{ (short)(fruitPos.X * 2),fruitPos.Y }, FRUITCOL);
	}

	void updateSnake() {
		if (dir != STOP) {
			//adds previous head position to the snake list 
			snake.push_back(headPos);
			createPix(COORD{ (short)(headPos.X * 2),headPos.Y }, SNAKEBODY);
		}
		//updates position 
		switch (dir) {
		case UP:
			headPos.Y--;
			break;
		case LEFT:
			headPos.X--;
			break;
		case RIGHT:
			headPos.X++;
			break;
		case DOWN:
			headPos.Y++;
			break;
		}
		//if snake collides with fruit 
		if (headPos.X == fruitPos.X && headPos.Y == fruitPos.Y) {
			//updates 
			updateFruit();
			moveTime = 70 * pow((1 / 1.25), len - 2) + 80;
			score += 100;
			updateScore();
			len++;
		}
		//tests collisions with walls 
		if (headPos.X <= 0 || headPos.Y <= 0 || headPos.X > dimensions.X || headPos.Y > dimensions.Y) gameOver = true;
		//prints head 
		createPix(COORD{ (short)(headPos.X * 2),headPos.Y }, SNAKEHEAD);
		//if the snake is too long 
		if (snake.size() >= len) {
			//removes the end of the snake 
			createPix(COORD{ (short)(snake[0].X * 2),snake[0].Y }, ENVIROCOL);
			snake.erase(snake.begin());
		}
		for (COORD i : snake) {
			if (i.X == headPos.X && i.Y == headPos.Y) {
				gameOver = true;
				dir = STOP;
			}
		}
	}

	void Update() {
		//updates current time 
		curTime = std::chrono::steady_clock::now();
		//updates snake after a certain amount of time 
		if (std::chrono::duration_cast<std::chrono::milliseconds>(curTime - lastMove).count() >= moveTime) {
			//updates direction and snake 
			dir = temp;
			updateSnake();
			//updates timer 
			lastMove = std::chrono::steady_clock::now();
		}
	}

	void Input() {
		//gets key states of WASD and changes the direction 
		if (GetKeyState(27) & 0x8000) gameOver = true;
		if (GetKeyState('W') & 0x8000 && dir != DOWN) temp = UP;
		if (GetKeyState('A') & 0x8000 && dir != RIGHT) temp = LEFT;
		if (GetKeyState('S') & 0x8000 && dir != UP) temp = DOWN;
		if (GetKeyState('D') & 0x8000 && dir != LEFT) temp = RIGHT;
	}
public:
	void play() {
		//init game 
		Setup();
		//loops until player dies 
		while (!gameOver) {
			Update();
			Input();
		}
		//creates game over msg 
		createText("GAME OVER", COORD{ (short)(dimensions.X - 2),(short)(dimensions.Y / 2) }, RED);
		createText("PRESS SPACE TO PLAY AGAIN", COORD{ (short)(dimensions.X - 10),(short)(dimensions.Y / 2 + 1) }, RED);
		createText("OR ESCAPE TO QUIT", COORD{ (short)(dimensions.X - 6),(short)(dimensions.Y / 2 + 2) }, RED);
		//resets console cursor 
		SetConsoleTextAttribute(hConsole, WHITE);
		SetConsoleCursorPosition(hConsole, COORD{ 0,(short)(dimensions.Y + 4) });
	}
};


int main() {
	Game snake;
	std::cout << "press space to start";
	while (true) {
		//starts game when space is pressed 
		if (GetKeyState(' ') & 0x8000) snake.play();
		//breaks if escape is pressed 
		else if (GetKeyState(27) & 0x8000) break;
	}
}