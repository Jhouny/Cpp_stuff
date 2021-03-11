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
#include<time.h>

using namespace std;
int height, width, shipX, shipY, dir, change, enemyY, enemyX, enemy_change, shift, score, level, kills, chance, Play();
bool gameOver;
bool state = false, quit = false, play = false;
char matrix[150][150], key, lastKey, text;
int directions[3] = {1, -1};

char row[5][200] = {
" #  ##   ## ##  ### ###  ## # # ###  ## # # #   # # ### ### ##   #  ##   ## ### # # # # # # # # # # ### ### #       ", "# # # # #   # # #   #   #   # #  #    # # # #   ### # # # # # # # # # # #    #  # # # # # # # # # #   #   # #       ", "### ##  #   # # ##  ##  # # ###  #    # ##  #   ### # # # # ##  # # ##   #   #  # # # # ###  #   #   #   ## #       ", "# # # # #   # # #   #   # # # #  #  # # # # #   # # # # # # #    ## # #   #  #  # # # # ### # #  #  #               ", "# # ##   ## ##  ### #    ## # # ###  #  # # ### # # # # ### #     # # # ##   #  ###  #  # # # #  #  ###  #  #       "
};

char row1[5][200] = {};
char alphabet[] = "abcdefghijklmnopqrstuvwxyz?! ";

class enemy_ship {
	public:
		int x, y, direction;
		enemy_ship() {
			x = rand() % (width-1-shift)+shift;
			y = rand() % (height-10)+1;
			direction = directions[rand() % 1];
		}
		int getX() { return x; }
		int getY() { return y; }
		int getDir() { return direction; }
};

class shot {
	public:
		int x, y, dir;
		shot(int a, int b, int c) {
			x = a;
			y = b;
			dir = c;
		}
		int getX() { return x; }
		int getY() { return y; }
};

class enemy_shot {
	public:
		int x, y, dir;
		enemy_shot(int a, int b, int c) {
			x = a;
			y = b;
			dir = c;
		}
		int getX() { return x; }
		int getY() { return y; }
};

//Create enemies and shots vector
vector<enemy_ship> enemies;
vector<enemy_ship>::iterator it;

vector<shot> ship_shots;
vector<shot>::iterator itr;

vector<enemy_shot> enemy_shots;
vector<enemy_shot>::iterator ens;

void Text() {
	char word[] = "level up!";
	system("clear");
	for(int j = 0; j < 5; j++) {
		for(int i = 0; i < 117; i++) {
			if(row[j][i] == '#') {
				row1[j][i] = 'O'; 
			}
			else {
				row1[j][i] = ' ';
			}
		}
	}
	for(int j = 0; j < 5; j++) {
		for(int i = 0; i < sizeof(word)-1; i++) {
			char* ch = strchr(alphabet, word[i]);
			int pos = ch-alphabet+1;
			int start = 4*pos-4;
			int end = 4*pos;
			for(int k = start; k < end; k++) {
				printf("%c", row1[j][k]);
				printf("%c", row1[j][k]);
			}
			printf(" ");
		}
		printf("\n");
	}
}

//Keyboard input
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

//Check user input
void Check() {
	while(!kbhit()) {
		//Update key value
		key = getchar();
		printf("Type 'q' to quit or 'r' to play the game: ");
		usleep(50000);
		system("clear");
	}

	if(key == 'q') {
		state = true;
		gameOver = true;
		printf("\n");
	}
	else if(key == 'r') {
		enemies.clear();
		ship_shots.clear();
		enemy_shots.clear();
		state = false;
		gameOver = false;
		kills = 0;
		level = 1;
		Play();
	}
	
	usleep(50000);
	/*
	if(key == 'q') {
		state = true;
		gameOver = true;
		printf("\n");
	}
	else if(key == 'r') {
		enemies.clear();
		ship_shots.clear();
		enemy_shots.clear();
		state = false;
		gameOver = false;
		kills = 0;
		level = 1;
		Play();
	}
	usleep(50000);*/
}


//Print the game Over message in the screen
void End() {
	system("clear");
	char word[] = "game over";
	for(int j = 0; j < 5; j++) {
		for(int i = 0; i < 113; i++) {
			if(row[j][i] == '#') {
				row1[j][i] = 'O'; 
			}
			else {
				row1[j][i] = ' ';
			}
		}
	}
	for(int j = 0; j < 5; j++) {
		for(int i = 0; i < sizeof(word)-1; i++) {
			char* ch = strchr(alphabet, word[i]);
			int pos = ch-alphabet+1;
			int start = 4*pos-4;
			int end = 4*pos;
			/*for(int i = 0; i < 40; i++) {
				pri1ntf("\n");
;			}*/
			for(int k = start; k < end; k++) {
				printf("%c", row1[j][k]);
				printf("%c", row1[j][k]);
			}
			printf(" ");
		}
		printf("\n");
	}
	//usleep(250000);
	printf("Press ENTER to continue...");
}

//Defining and printing the matrix
int draw() {
	//Clear the screen
	system("clear");	
	
	//Setting the matrix to empty spaces
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			matrix[j][i] = ' ';
		}
	}
	 
	//Set the map in the matrix
	for(int i = 0; i < width; i++) {
		matrix[i][0] = '#';
		matrix[i][height-1] = '#'; 
	}
	for(int i = 0; i < height; i++) {
		matrix[0][i] = '#';
		matrix[width-1][i] = '#';
	}

	//Define the next position of the ship
	if(dir == 0) {
		shipX = shipX - change;
	}
	else if(dir == 1) {
		shipX = shipX + change;		
	}
	
	//Set the enemies next positions and check for kills
	bool flag = false;
	int index = 2;
	for(it = enemies.begin(); it != enemies.end() && flag == false; it++) {
		if(it->x == rand() % (width-1-shift)+shift || it->x <= 0 || it->x >= width-3) {
			it->direction = it->direction*-1; 
		}
		it->x =  it->x + it->direction*level;
		
		for(itr = ship_shots.begin(); itr != ship_shots.end() && flag == false; itr++) {
			if(itr->y == it->y && itr->x == it->x || itr->y == it->y && itr->x == it->x+1 || itr->y == it->y && itr->x == it->x-1) {
				itr = ship_shots.erase(itr);
				it = enemies.erase(it);
				kills = kills + 1;
				flag = true;
			}		
		}		
		
		int num = (rand() % 10*index);
		index = index+1;
		if(num == 0) {
			enemy_shots.insert(enemy_shots.begin(), 1, enemy_shot(it->x, it->y, 1));
		}
	}
	flag = false;
	for(ens = enemy_shots.begin(); ens != enemy_shots.end() && flag == false; ens++) {
		if(ens->y == height) {
			ens = enemy_shots.erase(ens);
			flag = true;
		}
		else {
			for(itr = ship_shots.begin(); itr != ship_shots.end() && flag == false; itr++) {
				if(itr->y == ens->y && itr->x == ens->x) {
					ens = enemy_shots.erase(ens);
					itr = ship_shots.erase(itr);
				}
			}
		}
	}
	flag = false;
	for(itr = ship_shots.begin(); itr != ship_shots.end() && flag == false; itr++) {
		if(itr->y == 0) {
			itr = ship_shots.erase(itr);
			flag = true;
			//Print the total shots for counting to be possible
		}
	}
	
	flag = false;
	for(ens = enemy_shots.begin(); ens != enemy_shots.end() && flag == false; ens++) {
		if(ens->y == shipY && ens->x == shipX || ens->y == shipY && ens->x == shipX-1 || ens->y == shipY && ens->x == shipX+1) {
			ens = enemy_shots.erase(ens);
			gameOver = true;
			flag = true;
			End();
			Check();
//			Play();
			break;
		}
	}
	
		
				
	//Move the existing shots
	for(itr = ship_shots.begin(); itr != ship_shots.end(); itr++) {
		itr->y = itr->y + itr->dir;
			
	}
	for(ens = enemy_shots.begin(); ens != enemy_shots.end(); ens++) {
		ens->y = ens->y + ens->dir;
	}
	

	//Set the objects positions in the matrix
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width-2; j++) {
			if(i == shipY && j == shipX) {
				matrix[j-1][i] = '<';
				matrix[j][i] = '^';
				matrix[j+1][i] = '>';
			}
			for(it = enemies.begin(); it != enemies.end(); it++) {
				if(i == (*it).getY() && j == (*it).getX()) {
					matrix[j][i] = '(';
					matrix[j+1][i] = '=';
					matrix[j+2][i] = ')';				
	  			}
	  		}
	  		
	  		for(itr = ship_shots.begin(); itr != ship_shots.end(); itr++) {
	  			if(i == itr->y && j == itr->x) {
	  				matrix[j][i] = '|';
	  			}
	  		}
			
			for(ens = enemy_shots.begin(); ens != enemy_shots.end(); ens++) {
				if(i == ens->y && j == ens->x) {
					matrix[j][i] = '*';
				}
			}
		}
	}
	//Print the whole matrix
	if(gameOver == false) {
		for(int j = 0; j < height; j++) {	
			for(int i = 0; i < width + 30; i++) {
				//Show the scores and enemies left
				if(j == height/2 && i == width+1) {
					printf("Total Kills: %i", kills);
				}
				else if(j == 1+(height/2) && i == width+1) {
					printf("Level: %i", level);
				}

				else {
					printf("%c", matrix[i][j]);
				}
			}
			printf("\n");
		}
	}
	//}

	//Time to wait before next iteration
	usleep(100000);
}

int Play() {
	srand(time(NULL));
	shipX = width / 2;
	shipY = height - 3;
	enemies.insert(enemies.begin(), 1, enemy_ship());
	enemies.insert(enemies.begin(), 1, enemy_ship());
	while(!gameOver) {
		while(!kbhit() && gameOver == false) {
			draw();
			if(key == 'a' && gameOver == false) {
				dir = 0;
			}
			else if(key == 'd' && gameOver == false) {
				dir = 1;
			}
			time_t sec;
			chance = (sec%60);
			if(chance == rand() % 60 || chance%15==0) {
				enemies.insert(enemies.begin(), 1, enemy_ship());
			}
			else if(key == ' ' && gameOver == false) {
				ship_shots.insert(ship_shots.begin(), 1, shot(shipX, shipY, -1));
				if(kills == (5*level)) {
					kills = 0;
					level++;
					Text();
					usleep(2000000);
				}
				key = 'e';
			}

			if(shipX == 0 || shipX == width) {
				End();
				Check();
				gameOver = true;
				break;
				
			}
		}
		key = getchar();
		time_t sec;
		chance = sec%60;
		if(chance == rand() % 60 || chance%15==0) {
			enemies.insert(enemies.begin(), 1, enemy_ship());
		}
	}
	//Check();

}

int main(int argc, char *argv[]) {
	width = atoi(argv[1]);
	height = atoi(argv[2]);
	shift = 2;
	score = 0;
	chance = 0;
	dir = 2;
	level = 1;
	change = 1;
	gameOver = false;
	srand(time(NULL));
	shipX = width / 2;
	shipY = height - 3;
	system("clear");
	printf("Type 'q' to quit or 'r' to play the game: ");
	
	while(state == false) {
		Check();
	}
}
