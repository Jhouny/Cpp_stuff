#include<iostream>
#include<ncurses.h>
#include<unistd.h>

using namespace std;

int x = 0;
int y = 0;
int width = 20;
int height = 10;
int fruitX, fruitY; 

int draw() {
	system("clear");
	cout << "\nDrawing...\n";
	for(int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << "\n";
	
	for(int i = 0; i < height; i++) {
		cout << "#";
		for(int j = 0; j < width-2; j++) {
			if(j == x && i == y) {
				cout << "o";
			} else if(j == fruitX && i == fruitY) {
				cout << "F";
			} else {
				cout << " ";
			}
		}
		cout << "#\n";
	}
	for(int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << "\n";
}

int input() {
	int ch = getch();
	if(ch == 119) {
		printw("'W' was pressed");
	}
}

int main() {
	int X = rand();
	int Y = rand();
	fruitX = X % width;
	cout << "fruitX is " << fruitX;
	fruitY = Y % height;
	cout << "fruitY is " << fruitY;
	while(1) {
		draw();
		input();
		sleep(1);
	}
}
