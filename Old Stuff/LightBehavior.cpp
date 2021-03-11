#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<termios.h>
#include<unistd.h>
#include<fcntl.h>
#include<iostream>
#include<list>
#include <string.h> 
#include <bits/stdc++.h>  

using namespace std;
int height, width, dir, shift, score, kills;
bool gameOver;
char matrix[150][150], key, lastKey, text;
int directions[3] = {1, -1};

char row[5][200] = {
" #  ##   ## ##  ### ###  ## # # ###  ## # # #   # # ### ### ##   #  ##   ## ### # # # # # # # # # # ### ### #       ", "# # # # #   # # #   #   #   # #  #    # # # #   ### # # # # # # # # # # #    #  # # # # # # # # # #   #   # #       ", "### ##  #   # # ##  ##  # # ###  #    # ##  #   ### # # # # ##  # # ##   #   #  # # # # ###  #   #   #   ## #       ", "# # # # #   # # #   #   # # # #  #  # # # # #   # # # # # # #    ## # #   #  #  # # # # ### # #  #  #               ", "# # ##   ## ##  ### #    ## # # ###  #  # # ### # # # # ### #     # # # ##   #  ###  #  # # # #  #  ###  #  #       "
};
char row1[5][200] = {};
char alphabet[] = "abcdefghijklmnopqrstuvwxyz?! ";

class bulb {
	public:
		int x, y;
		bulb() {
			x = width/2;
			y = height-3;
		}
		int getX() { return x; }
		int getY() { return y; }
};

class obstacle {
	public:
		int x, y;
		obstacle(int i, int j) {
			x = i;
			y = j;
		}
		int getX() { return x; }
		int getY() { return y; }
};

//Create the obstacles and sources vectors
vector<obstacle> obstacles;
vector<obstacle>::iterator it;

vector<bulb> sources;
vector<bulb>::iterator itr;

int draw() {
	//Clear the screen
	system("clear");	
	
	//Setting the matrix to empty spaces
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			matrix[i][j] = '*';
		}
	}
	 
	//Set the map in the matrix
	for(int j = 0; j < width; j++) {
		matrix[0][j] = '#';
		matrix[height-1][j] = '#'; 
	}
	for(int i = 0; i < height; i++) {
		matrix[i][0] = '#';
		matrix[i][width-1] = '#';
	}
	
	//Set the objects positions
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(it = obstacles.begin(); it != obstacles.end(); it++) {
				if(i == (*it).getY() && j == (*it).getX()) {
					matrix[i][j] = '#';
				}
			}
			for(itr = sources.begin(); itr != sources.end(); itr++) {
				if(i == (*itr).getY() && j == (*itr).getX()) {
					matrix[i][j] = 'O';
				}
			}
		}
	}
	//Print the whole matrix 
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			printf("%c", matrix[i][j]);
		}
		printf("\n");
	}
	usleep(80000);
}

int kbhit() {
	struct termios oldt, newt;
	int ch;
	int oldf;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if(ch != EOF) {
	  ungetc(ch, stdin);
	  return 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	width = atoi(argv[1]);
	height = atoi(argv[2]);
	shift = 2;
	score = 0;
	dir = 2;
	gameOver = false;
	srand(time(NULL));
	char direction[2] = {-1, 1};
	/*
	for(int i = 0; i < (rand() % (50)+10); i++) {
		int curX = rand() % (width-1)+1;
		int curY = rand() % (height-1)+1;
		int Xchange = pow(-1, (rand()%3));
		int Ychange = pow(-1, (rand()%3));
		obstacles.insert(obstacles.begin(), 1, obstacle(curX, curY));
		if(curY < height/2 && curX < width/2) {
			obstacles.insert(obstacles.begin(), 1, obstacle(curX+1, curY+1));
		}
		else if(curY < height/2 && curX > width/2) {
			obstacles.insert(obstacles.begin(), 1, obstacle(curX-1, curY+1));
		}
		else if(curY > height/2 && curX < width/2) {
			obstacles.insert(obstacles.begin(), 1, obstacle(curX+1, curY-1));
		}
		else if(curY > height/2 && curX > width/2) {
			obstacles.insert(obstacles.begin(), 1, obstacle(curX-1, curY-1));
		}
		else if(curY == height/2 && curX > width/2) {
			obstacles.insert(obstacles.begin(), 1, obstacle(curX-1, curY));
		}
		else if(curY == height/2 && curX < width/2) {
			obstacles.insert(obstacles.begin(), 1, obstacle(curX+1, curY));
		}
		else if(curY > height/2 && curX == width/2) {
			obstacles.insert(obstacles.begin(), 1, obstacle(curX, curY-1));
		}
		else if(curY < height/2 && curX == width/2) {
			obstacles.insert(obstacles.begin(), 1, obstacle(curX, curY+1));
		}
		else if(curY == height/2 && curX == width/2) {
			obstacles.insert(obstacles.begin(), 1, obstacle(curX, curY));
		}
		
	}*/
	
	sources.insert(sources.begin(), 1, bulb());
	for(int e = 1; e < 20; e++) {
		obstacles.insert(obstacles.begin(), 1, obstacle(e, height/2));
	}
	while(!gameOver) {
		draw();
	}	
}
