#include<iostream>
#include<string>
//#include<conio.h>
#include<unistd.h>

using namespace std;
bool gameOver = false;
int width = 10;
int height = 10;
int x, y, fruitX, fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

int hello() {
	string s;
	cout << "Your Name: ";
	cin >> s;
	cout << "Hello, " << s << '\n';
}

int draw() {
	system("clear");
	for(int i = 0; i < width; i++){
		cout << "#";
	}
	cout << "\n";
	for(int i = 0; i < height; i++){
		cout << "#";
		for(int j = 0; j < width-2; j++){
			if(j == x && i == y){
				cout << "O";
			}
			else if(j == fruitX && i == fruitY) {
				cout << "F";
			}
			else {
				cout << " ";	
			}
		}
		cout << "#\n";
	}
	for(int i = 0; i < width; i++){
		cout << "#";
	}
	cout << "\n";
}

//int input() {
//	if(_kbhit()){
//		switch(_getch()){
//			case 'a':
//				dir = LEFT;
//				break;
//			case 'd':
//				dir = RIGHT;
//				break;
//			case 'w':
//				dir = UP;
//				break;
//			case 's':
//				dir = DOWN;
//				break;
//			case 'q':
//				gameOver = true;
//				break;	
//		}	
//	}
//}

//int logic() {
//	switch(dir){
//		case LEFT:
//			x--;
//			break;
//		case RIGHT:
//			x++;
//			break;
//		case UP:
//			y--;
//			break;
//		case DOWN:
//			y++;
//			break;
//		default:
//			break;
//	}
//}

int main() {
	hello();
	x = width/2;
	y = height/2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

	while(!gameOver){
		draw();
		sleep(1);
	}
	return 0;
}
