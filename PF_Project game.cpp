#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#include "myconsole.h"
#include "mygraphics.h"
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")



#include<windows.h>    //used for PlaySound function
#include<fstream>    
using namespace std;

bool game_end = false;

COLORREF white = RGB(255, 255, 255);
COLORREF skin = RGB(236, 188, 180);
COLORREF black = RGB(0, 0, 0);
COLORREF red = RGB(255, 0, 0);
COLORREF gray = RGB(50, 50, 50);
COLORREF green = RGB(34, 139, 34);
COLORREF blue = RGB(0, 0, 128);
COLORREF yellow = RGB(255, 255, 0);
COLORREF cyan = RGB(0, 255, 255);
int x_1 = 370, x_2 = 550;
int rodPositionX1 = 370;
int rodPositionX2 = 550;
int dir = 1; // intial hit at center
int boardCoord[6][12];
int boardCoordY[6][12];
int shapes[6][12];
int rectHit[12] = { 320,320,320,320,320,320,320,320,320,320,320,320 };
ofstream fout;

//void playMusic(char* path) {
//	mciSendString((LPCWSTR)path, NULL, 0, NULL);
//	mciSendString((LPCWSTR)"play mp3", NULL, 0, NULL);
//}
void Shapes() {

	int i = 0, j = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 12; j++) {
			shapes[i][j] = 0;
		}
	}
}
void bricks() {
	int horizontalCoordinates[12][6] = { {20,80},{90,160},{170,240},{250,320},{330,400},{410,480 },{490,560},{640,710},{790,860},{870,940},{950,1020} };

	int hasHit[6][12];
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 12; j++) {
			hasHit[i][j] = 1;
		}
	}
}
//function Prototypes and definition.
void triangle(int, int, int);
int Rand() {
	srand((unsigned)time(0));
	int rnd;
	rnd = (rand() % 2) + 1;
	return rnd;
}
void Border() {
	// variable i is used to control border width. 
	for (int i = 0; i < 6; i++) {
		//myLine(0, 540, 0, 0, yellow);
		myLine(i, 540, i, 0, yellow);
		//myLine(2, 540, 0, 0, yellow);
		//right
		//myLine(975, 540, 975, 0, yellow);
		myLine(975 + i, 540 + i, 975 + i, i, yellow);
		//up
		myLine(0, i, 975, i, yellow);
		//myLine(0, 0, 975, 2, yellow);
		//down
		myLine(975, 540 + i, i, 540 + i, yellow);
	}
}
int checkClosest(int board[][12], int c)
{
	int closest = board[0][0];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 12; j++)
		{
			if (board[i][j] - c <= board[i][j] - closest) {
				closest = board[i][j];
			}
		}
	}
	return closest;
}
void Pattern1() {
	int H1 = 0, V1=0;
	//2 for Squares,1 for Rectangles,3 for triangles,4 for circles;
	myRect(593, 40, 615, 60, black, yellow);
	H1 = checkClosest(boardCoord, 593);
	V1 = checkClosest(boardCoordY, 40);
	shapes[V1 / 50][H1 / 80] = 2;

	myRect(753, 240, 775, 260, black, yellow);
	H1 = checkClosest(boardCoord, 753);
	V1 = checkClosest(boardCoordY, 240);
	shapes[V1 / 50][H1 / 80] = 2;

	myRect(433, 140, 455, 160, black, yellow);
	H1 = checkClosest(boardCoord, 433);
	V1 = checkClosest(boardCoordY, 140);
	shapes[V1 / 50][H1 / 80] = 2;

	myRect(273, 90, 295, 110, black, yellow);
	H1 = checkClosest(boardCoord, 273);
	V1 = checkClosest(boardCoordY, 90);
	shapes[V1 / 50][H1 / 80] = 2;

	myEllipse(30, 140, 60, 158, black, green);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 140);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(30, 290, 60, 308, black, green);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 290);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(910, 40, 940, 58, black, green);
	H1 = checkClosest(boardCoord, 910);
	V1 = checkClosest(boardCoordY, 40);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(350, 290, 380, 308, black, green);
	H1 = checkClosest(boardCoord, 350);
	V1 = checkClosest(boardCoordY, 290);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(110, 90, 140, 108, black, green);
	H1 = checkClosest(boardCoord, 110);
	V1 = checkClosest(boardCoordY, 90);
	shapes[V1 / 50][H1 / 80] = 4;


	triangle(445, 105, 10);
	H1 = checkClosest(boardCoord, 445);
	V1 = checkClosest(boardCoordY, 105);
	shapes[V1 / 50][H1 / 80] = 3;

	triangle(685, 210, 10);
	H1 = checkClosest(boardCoord, 685);
	V1 = checkClosest(boardCoordY, 210);
	shapes[V1 / 50][H1 / 80] = 3;

	triangle(925, 264, 10);
	H1 = checkClosest(boardCoord, 925);
	V1 = checkClosest(boardCoordY, 264);
	shapes[V1 / 50][H1 / 80] = 3;

	myRect(830, 42, 860, 57, black, gray);
	H1 = checkClosest(boardCoord, 830);
	V1 = checkClosest(boardCoordY, 42);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(830, 292, 860, 307, black, gray);
	H1 = checkClosest(boardCoord, 830);
	V1 = checkClosest(boardCoordY, 292);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(30, 42, 60, 57, black, gray);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 42);
	shapes[V1 / 50][H1 / 80] = 1;
}
void Pattern2() {
	int H1 = 0, V1 = 0;
	//2 for Squares,1 for Rectangles,3 for triangles,4 for circles;
	myRect(753, 240, 775, 260, black, yellow);
	H1 = checkClosest(boardCoord, 753);
	V1 = checkClosest(boardCoordY, 240);
	shapes[V1 / 50][H1 / 80] = 2;

	myRect(513, 240, 535, 260, black, yellow);
	H1 = checkClosest(boardCoord, 513);
	V1 = checkClosest(boardCoordY, 240);
	shapes[V1 / 50][H1 / 80] = 2;

	myRect(593, 40, 615, 60, black, yellow);
	H1 = checkClosest(boardCoord, 593);
	V1 = checkClosest(boardCoordY, 40);
	shapes[V1 / 50][H1 / 80] = 2;

	myRect(113, 40, 135, 60, black, yellow);
	H1 = checkClosest(boardCoord, 113);
	V1 = checkClosest(boardCoordY, 40);
	shapes[V1 / 50][H1 / 80] = 2;



	myEllipse(110, 90, 140, 108, black, green);
	H1 = checkClosest(boardCoord, 110);
	V1 = checkClosest(boardCoordY, 90);
	shapes[V1 / 50][H1 / 80] = 4;


	myEllipse(30, 140, 60, 158, black, green);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 140);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(910, 40, 940, 58, black, green);
	H1 = checkClosest(boardCoord, 910);
	V1 = checkClosest(boardCoordY, 40);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(30, 290, 60, 308, black, green);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 290);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(350, 290, 380, 308, black, green);
	H1 = checkClosest(boardCoord, 350);
	V1 = checkClosest(boardCoordY, 290);
	shapes[V1 / 50][H1 / 80] = 4;

	triangle(125, 156, 10);
	H1 = checkClosest(boardCoord, 125);
	V1 = checkClosest(boardCoordY, 156);
	shapes[V1 / 50][H1 / 80] = 3;

	triangle(925, 156, 10);
	H1 = checkClosest(boardCoord, 925);
	V1 = checkClosest(boardCoordY, 156);
	shapes[V1 / 50][H1 / 80] = 3;

	triangle(925, 264, 10);
	H1 = checkClosest(boardCoord, 925);
	V1 = checkClosest(boardCoordY, 264);
	shapes[V1 / 50][H1 / 80] = 3;

	triangle(205, 210, 10);
	H1 = checkClosest(boardCoord, 205);
	V1 = checkClosest(boardCoordY, 210);
	shapes[V1 / 50][H1 / 80] = 3;

	myRect(830, 292, 860, 307, black, gray);
	H1 = checkClosest(boardCoord, 830);
	V1 = checkClosest(boardCoordY, 292);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(830, 42, 860, 57, black, gray);
	H1 = checkClosest(boardCoord, 830);
	V1 = checkClosest(boardCoordY, 42);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(30, 92, 60, 107, black, gray);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 92);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(190, 42, 220, 57, black, gray);
	H1 = checkClosest(boardCoord, 190);
	V1 = checkClosest(boardCoordY, 42);
	shapes[V1 / 50][H1 / 80] = 1;
}
void Pattern3() {
	int H1 = 0, V1=0;
	//2 for Squares,1 for Rectangles,3 for triangles,4 for circles;
	myRect(113, 290, 135, 310, black, yellow);
	H1 = checkClosest(boardCoord, 113);
	V1 = checkClosest(boardCoordY, 290);
	shapes[V1 / 50][H1 / 80] = 2;

	myRect(33, 190, 55, 210, black, yellow);
	H1 = checkClosest(boardCoord, 33);
	V1 = checkClosest(boardCoordY, 190);
	shapes[V1 / 50][H1 / 80] = 2;

	myRect(433, 140, 455, 160, black, yellow);
	H1 = checkClosest(boardCoord, 433);
	V1 = checkClosest(boardCoordY, 140);
	shapes[V1 / 50][H1 / 80] = 2;

	myEllipse(110, 90, 140, 108, black, green);
	H1 = checkClosest(boardCoord, 110);
	V1 = checkClosest(boardCoordY, 90);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(30, 140, 60, 158, black, green);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 140);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(30, 290, 60, 308, black, green);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 290);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(590, 290, 620, 308, black, green);
	H1 = checkClosest(boardCoord, 590);
	V1 = checkClosest(boardCoordY, 290);
	shapes[V1 / 50][H1 / 80] = 4;

	myEllipse(430, 190, 460, 208, black, green);
	H1 = checkClosest(boardCoord, 430);
	V1 = checkClosest(boardCoordY, 190);
	shapes[V1 / 50][H1 / 80] =4;

	triangle(925, 156, 10);
	H1 = checkClosest(boardCoord, 925);
	V1 = checkClosest(boardCoordY, 156);
	shapes[V1 / 50][H1 / 80] = 3;

	triangle(445, 105, 10);
	H1 = checkClosest(boardCoord, 445);
	V1 = checkClosest(boardCoordY, 105);
	shapes[V1 / 50][H1 / 80] = 3;

	triangle(685, 210, 10);
	H1 = checkClosest(boardCoord, 685);
	V1 = checkClosest(boardCoordY, 210);
	shapes[V1 / 50][H1 / 80] =3;

	triangle(925, 264, 10);
	H1 = checkClosest(boardCoord, 925);
	V1 = checkClosest(boardCoordY, 264);
	shapes[V1 / 50][H1 / 80] = 3;

	myRect(30, 42, 60, 57, black, gray);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 42);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(108, 192, 138, 207, black, gray);
	H1 = checkClosest(boardCoord, 108);
	V1 = checkClosest(boardCoordY, 192);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(30, 92, 60, 107, black, gray);
	H1 = checkClosest(boardCoord, 30);
	V1 = checkClosest(boardCoordY, 92);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(190, 42, 220, 57, black, gray);
	H1 = checkClosest(boardCoord, 190);
	V1 = checkClosest(boardCoordY, 42);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(350, 242, 380, 257, black, gray);
	H1 = checkClosest(boardCoord, 350);
	V1 = checkClosest(boardCoordY, 242);
	shapes[V1 / 50][H1 / 80] = 1;

	myRect(510, 292, 540, 307, black, gray);
	H1 = checkClosest(boardCoord, 510);
	V1 = checkClosest(boardCoordY, 292);
	shapes[V1 / 50][H1 / 80] = 1;
}
void printScore(int score) {
	char X[150] = "SCORE :";
	score = score + 2;
	char buff[10];
	char Y[150] = "Score :";
	_itoa_s(score, buff, 10);
	strcat_s(Y, buff);
	myDrawTextWithFont(1000, 15, 25, X, black, white);
}
void Lives(float lives) {
	lives = lives - 0.5;
	char Y[150] = "Lives :";
	char buff[10];
	_itoa_s(lives, buff, 10);
	strcat_s(Y, buff);
	myDrawTextWithFont(1000, 45, 25, Y, black, white);
}
void Gameover() {
	char s[150] = "Game Over!";
	//PlaySound(TEXT("gameover.wav"), NULL, SND_SYNC);
	ClearScreen();
	for (int i = 0; i < 3; i++) {
		myDrawTextWithFont(60, 90, 90, s, black, white);
		Sleep(100);
		myDrawTextWithFont(60, 90, 90, s, black, red);
		Sleep(100);
		myDrawTextWithFont(60, 90, 90, s, black, green);
		Sleep(100);
		myDrawTextWithFont(60, 90, 90, s, black, skin);
		Sleep(100);
		myDrawTextWithFont(60, 90, 90, s, black, cyan);
	}
}
void Start() {
	char s[150] = "---------------------------------------------- \n Welcome to Brick Breaker Game.\n ----------------------------------------------";
	for (int i = 0; i < 4; i++) {
		myDrawTextWithFont(60, 90, 90, s, black, white);
		Sleep(100);
		myDrawTextWithFont(60, 90, 90, s, black, red);
		Sleep(100);
		myDrawTextWithFont(60, 90, 90, s, black, green);
		Sleep(100);
		myDrawTextWithFont(60, 90, 90, s, black, skin);
		Sleep(100);
		myDrawTextWithFont(60, 90, 90, s, black, cyan);
	}
	ClearScreen();
}
void printSquares() {
	myRect(593, 40, 615, 60, black, yellow);
	myRect(113, 40, 135, 60, black, yellow);
	myRect(113, 290, 135, 310, black, yellow);
	myRect(33, 190, 55, 210, black, yellow);
	myRect(433, 140, 455, 160, black, yellow);
	myRect(273, 90, 295, 110, black, yellow);
	myRect(753, 90, 775, 110, black, yellow);
	myRect(833, 190, 855, 210, black, yellow);
	myRect(753, 240, 775, 260, black, yellow);
	myRect(513, 240, 535, 260, black, yellow);
}
void triangle(int x1, int y1, int size) {

	for (int i = -size; i < size; i++)
	{
		myLine(x1, y1, x1 - i, y1 - 20, red);
	}
}
void printCircle() {
	myEllipse(910, 40, 940, 58, black, green);
	myEllipse(110, 90, 140, 108, black, green);
	myEllipse(30, 140, 60, 158, black, green);
	myEllipse(30, 290, 60, 308, black, green);
	myEllipse(350, 290, 380, 308, black, green);
	myEllipse(590, 290, 620, 308, black, green);
	myEllipse(430, 190, 460, 208, black, green);
}
void printTriangles() {
	triangle(125, 156, 10);
	triangle(925, 156, 10);
	triangle(445, 105, 10);
	triangle(685, 210, 10);
	triangle(925, 264, 10);
	triangle(205, 210, 10);
	triangle(365, 159, 10);
	triangle(285, 310, 10);
}
void printRect() {
	myRect(30, 42, 60, 57, black, gray);
	myRect(108, 192, 138, 207, black, gray);
	myRect(30, 92, 60, 107, black, gray);
	myRect(190, 42, 220, 57, black, gray);
	myRect(350, 242, 380, 257, black, gray);
	myRect(510, 292, 540, 307, black, gray);
	myRect(670, 142, 700, 157, black, gray);
	myRect(350, 42, 380, 57, black, gray);
	myRect(830, 42, 860, 57, black, gray);
	myRect(830, 292, 860, 307, black, gray);
	myRect(830, 42, 860, 57, black, gray);
	myRect(510, 92, 540, 107, black, gray);
	myRect(30, 242, 60, 257, black, gray);
}
void PatternDef() {
	printCircle();
	printTriangles();
	printRect();
	printSquares();
}
void MoveLine(char ch) {
	if (ch == 'd' && x_2 < 875) {
		myLine(x_1, 500, x_2, 500, black);
		myLine(x_1, 501, x_2, 501, black);
		myLine(x_1, 502, x_2, 502, black);
		myLine(x_1, 503, x_2, 503, black);
		myLine(x_1, 504, x_2, 504, black);
		x_1 = x_1 + 180;
		x_2 = x_2 + 200;
		dir = 3;
		myLine(x_1, 500, x_2, 500, cyan);
		myLine(x_1, 501, x_2, 501, cyan);
		myLine(x_1, 502, x_2, 502, cyan);
		myLine(x_1, 503, x_2, 503, cyan);
		myLine(x_1, 504, x_2, 504, red);
		
		ch = 0;
	}
	//right movement
	else if (ch == 'a' && x_1 > 10) {
		myLine(x_1, 500, x_2, 500, black);
		myLine(x_1, 501, x_2, 501, black);
		myLine(x_1, 502, x_2, 502, black);
		myLine(x_1, 503, x_2, 503, black);
		myLine(x_1, 504, x_2, 504, black);
		x_1 = x_1 - 180;
		x_2 = x_2 - 200;
		dir = 2;
		myLine(x_1, 500, x_2, 500, cyan);
		myLine(x_1, 501, x_2, 501, cyan);
		myLine(x_1, 502, x_2, 502, cyan);
		myLine(x_1, 503, x_2, 503, cyan);
		myLine(x_1, 504, x_2, 504, red);
		ch = 0;

	}
	else if (x_1 == 10 && x_2 == 80) {
		dir = 1;
	}

	rodPositionX1 = x_1;
	rodPositionX2 = x_2;
}
void makeBoard() {
	int x1, y1, x2, dist = 0, y2;
	x1 = 10, y1 = 30, x2 = 80, y2 = 70;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 12; j++) {

			myRect(x1 + dist, y1, x2 + dist, y2, white, skin);

			dist = 80 + dist;

			boardCoord[i][j] = x1 + dist;
			boardCoordY[i][j] = y1;
		}

		dist = 0;
		y1 = y2 + 10;
		y2 = y2 + 50;

	}
}

void printBall(int& C1, int& C2, int& C3, int& C4, int& c_1, int& c_2, int& c_3, int& c_4,int dir,bool once) 
{
	if (dir == 1) {
		C2 = c_2;
		C4 = c_4;
		c_2 = c_2 + 30; c_4 = c_4 + 30;
		myEllipse(C1, C2, C3, C4, black, black);
		myEllipse(c_1, c_2, c_3, c_4, cyan, white);


	}
	if (dir == 2) {
		C1 = c_1;
		C2 = c_2;
		C3 = c_3;
		C4 = c_4;
		c_2 = c_2 + 30; c_4 = c_4 + 30;
		if (once == true) {
			c_1 = c_1 + 10; c_3 = c_3 + 10;
		}
		myEllipse(C1, C2, C3, C4, black, black);
		myEllipse(c_1, c_2, c_3, c_4, cyan, white);


	}
	if (dir == 3) {
		C1 = c_1;
		C2 = c_2;
		C3 = c_3;
		C4 = c_4;
		c_2 = c_2 + 30; c_4 = c_4 + 30;
		if (once == true) {
			c_1 = c_1 - 10; c_3 = c_3 - 10;
		}


		myEllipse(C1, C2, C3, C4, black, black);
		myEllipse(c_1, c_2, c_3, c_4, cyan, white);


	}

}
void Menu() {
	ClearScreen();
	char x[150] = "Start new game : Press a";
	myDrawTextWithFont(10, 30, 90, x, black, white);
	char i[150] = "Show score history : Press s";
	myDrawTextWithFont(10, 120, 100, i, black, white);
	char s[150] = "Exit : Press e";
	myDrawTextWithFont(10, 220, 100, s, black, white);
	Sleep(100);

}
int main()
{

	//calling functions
	PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	Menu();
	char choice = _getch();
	if (choice == 's') {

	}
	if (choice == 'e') {
		game_end = true;
	}
	ClearScreen();

	Start();

	Border();
	makeBoard();


	if (Rand() == 1) {
		Pattern1();
	}
	else if (Rand() == 2) {
		Pattern2();
	}
	else if (Rand() == 3) {
		Pattern3();
	}

	//Ball Initialization.
	myEllipse(450, 470, 480, 500, cyan, white);
	//Centre  ||  Initialization.

	myLine(370, 500, 550, 500, white);
	myLine(370, 501, 550, 501, white);
	myLine(370, 502, 550, 502, white);
	myLine(370, 503, 550, 503, white);
	myLine(370, 504, 550, 504, white);

	if (choice == 'e') {
		ClearScreen();
		game_end = true;
		ClearScreen();
	}
	
	bool trig = true;
	int score = 0;
	float lives = 3;
	int b1 = 490, b2 = 230;
	int c_1 = 450, c_2 = 470, c_3 = 480, c_4 = 500; //White ball variables
	int C1 = 450, C2 = 470, C3 = 480, C4 = 500; //Black ball variables
	char ch = 's';
	bool trigger = false;
	int brickHitVertical = 320; int brickHitVertical2 = 300;
	int V1 = 280, V2 = 320;
	int H1 = 410, H2 = 480;
	
	int yPosition = 500;

	while(ch != 32) {
		ch = _getch();

	}
	
	while (game_end == false && trig==true) {
		printScore(score);
		Lives(lives);
		Sleep(50);
		bool hitTwice = false;
		if (_kbhit()) {
			ch = _getch();
			if (ch == 32) {
				while (ch == 32 && hitTwice==false) {
					if (_kbhit()) {
						ch = _getch();
						if (ch == 32) {
							hitTwice = true;
						}
					}
				}
			}
			else if (ch == 'd' || ch == 'a')
			{
				MoveLine(ch);
			}
		}

		if (c_2 < 20 || c_2 < rectHit[H1/80] || c_1<=10 || c_3>975) {

			Border();
			//
			C1 = c_1;
			C3 = c_3;
			//
			C2 = c_2;
			C4 = c_4;

			//coming down
			//Sleep(250);
			hitTwice = false;
			if (_kbhit()) {
				ch = _getch();
				if (ch == 32) {
					while (ch == 32 && hitTwice == false) {
						if (_kbhit()) {
							ch = _getch();
							if (ch == 32) {
								hitTwice = true;
							}
						}
					}
				}
				else if (ch == 'd' || ch == 'a')
				{
					MoveLine(ch);
				}
			}
			if ( c_1 < rodPositionX1 || c_3 > rodPositionX2) {
				while (c_4<505) {
					Sleep(250);
					printBall(C1, C2, C3, C4, c_1, c_2, c_3, c_4, dir,false);
				}
				game_end = true;
				Gameover();

			}
			bool once = true;
			//coming down
			hitTwice = false;
			if (_kbhit()) {
				ch = _getch();
				if (ch == 32) {
					while (ch == 32 && hitTwice == false) {
						if (_kbhit()) {
							ch = _getch();
							if (ch == 32) {
								hitTwice = true;
							}
						}
					}
				}
				else if (ch == 'd' || ch == 'a')
				{
					MoveLine(ch);
				}
			}
			while (c_1 > rodPositionX1 && c_3 < rodPositionX2 && c_4<yPosition) {
				
				printBall(C1, C2, C3, C4, c_1, c_2, c_3, c_4,dir,once);
				once = false;
				Border();
				Sleep(30);
			}
			C2 = c_2;
			C4 = c_4;
		
			rectHit[(H1 / 80)] = rectHit[H1 / 80] - 50;
			trigger = true;
		}
		else {
			if (trigger == false) {
				C2 = c_2 + 30;
				C4 = c_4 + 30;
			}
			hitTwice = false;
			if (_kbhit()) {
				ch = _getch();
				if (ch == 32) {
					while (ch == 32 && hitTwice == false) {
						if (_kbhit()) {
							ch = _getch();
							if (ch == 32) {
								hitTwice = true;
							}
						}
					}
				}
			}
			if (dir == 1) {
				myEllipse(C1, C2, C3, C4, black, black);
				myEllipse(c_1, c_2, c_3, c_4, cyan, white);
				c_2 = c_2 - 30; c_4 = c_4 - 30;
				if (c_2 < V2) {
					myRect(H1, V1, H2, V2, black, black);
					V1 = V1 - 50; V2 = V2 - 50;
					if (shapes[V1 / 50][H1 / 80] == 1) {
						score = score - 5;
						printScore(score);
					}
					else if (shapes[V1 / 50][H1 / 80] == 2) {
						score = score + 10;
						printScore(score);
					}
					else if (shapes[V1/ 50][H1 / 80] == 3) {
						lives = lives - 0.5;
						Lives(lives);
					}
					else if (shapes[V1 / 50][H1 / 80] == 4) {
						if (lives <= 5) {
							lives = lives + 1;
							Lives(lives);
						}
						else {
							score = score + 10;
							printScore(score);
						}
					}
					if (lives < 0.5) {
						Gameover();
					}
				}
			}
			else if (dir == 2) {
				C1 = c_1;
				C3 = c_3;
				C2 = c_2;
				C4 = c_4;

				H2 = checkClosest(boardCoord, c_1);
				H1 = H2 - 80;
				V1 = checkClosest(boardCoordY, c_2);
				V2=V1+50;

				c_1 = c_1 - 30; c_3 = c_3 - 30;
				c_2 = c_2 - 30; c_4 = c_4 - 30;
				//to ensure that border is not touched
				if (c_1 > 10) {
					myEllipse(C1, C2, C3, C4, black, black);
					myEllipse(c_1, c_2, c_3, c_4, cyan, white);

					if (c_1 < H2) {

						myRect(H1, V1, H2, V2, black, black);

						if (shapes[V1 / 50][H1 / 80] == 1) {
							score = score - 5;
							printScore(score);
						}
						else if (shapes[V1 / 50][H1 / 80] == 2) {
							score = score + 10;
							printScore(score);
						}
						else if (shapes[V1 / 50][H1 / 80] == 3) {
							lives = lives - 0.5;
							Lives(lives);
						}
						else if (shapes[V1 / 50][H1 / 80] == 4) {
							if (lives <= 5) {
								lives = lives + 1;
								Lives(lives);
							}
							else {
								score = score + 10;
								printScore(score);
							}
						}
						if (lives < 0.5) {
							Gameover();
						}

					}
				}
			}
			else if (dir == 3)
			{
				C1 = c_1;
				C3 = c_3;

				C2 = c_2;
				C4 = c_4;

				H1 = checkClosest(boardCoord, c_1);
				H2 = H1 + 80;
				V1 = checkClosest(boardCoordY, c_2);
				V2 = V1 + 50;
				c_1 = c_1 + 30; c_3 = c_3 + 30;
				c_2 = c_2 - 30; c_4 = c_4 - 30;
				//to ensure that border is not touched
				if (c_3 < 975) {
					myEllipse(C1, C2, C3, C4, black, black);
					myEllipse(c_1, c_2, c_3, c_4, cyan, white);

					if (c_3 >= H1) {
						myRect(H1, V1, H2, V2, black, black);

						if (shapes[V1 / 50][H1 / 80] == 1) {
							score = score - 5;
							printScore(score);
						}
						else if (shapes[V1 / 50][H1 / 80] == 2) {
							score = score + 10;
							printScore(score);
						}
						else if (shapes[V1 / 50][H1 / 80] == 3) {
							lives = lives - 0.5;
							Lives(lives);
						}
						else if (shapes[V1 / 50][H1 / 80] == 4) {
							if (lives <= 5) {
								lives = lives + 1;
								Lives(lives);
							}
							else {
								score = score + 10;
								printScore(score);
							}
						}
						if (lives < 0.5) {
							Gameover();
						}

					}
				}
			}
			trigger = false;
		}
		
		
	}

	fout.open("scoreHistory.txt");
	fout <<"Score is: " <<score;
	

	//cursor function for endl.
	for (int u = 0; u < 23; u++) {
		cout << endl;
	}
	cout << endl;
}

