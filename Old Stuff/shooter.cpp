#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include<iostream>

typedef struct _ponto{
	int x;
	int y;
} Ponto;

typedef struct _fila {
	int ini;
	int fim;
	int tam;
	Ponto *vetor;
} Fila;

using namespace std;

bool gameOver = false;
int x, y, prizeX, prizeY,score, height, width, snakeSize, dir, next_x, next_y;
char matriz[500][500];
int shift = 2;

Fila* create_queue (int tam) {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = 0;
    f->fim = 0;
    f->tam = tam;
    f->vetor = (Ponto *)malloc(tam * sizeof(Ponto));
    return f;
}

void enqueue (Fila *f, int x, int y, int end) {
    Ponto a;
    a.x = x;
    a.y = y;
    f->vetor[f->fim] = a;
    f->fim = (end + 1);
}

Ponto dequeue (Fila *f) {
    Ponto a = f->vetor[f->fim];
    f->fim = (f->fim - 1);
    return a;
}

Ponto frente(Fila *f) {
    //return f->vetor[f->fim-1];
    return f->vetor[f->ini];
}

int draw(Fila *Snake) {
	//system("clear");
	for(int j = 0; j < height; j++) {
		for(int i = 0; i < width; i++) {
			matriz[i][j] = ' ';
		} 
	}
	for(int i = 0; i < width; i++) {
		matriz[i][0] = '#';
		matriz[i][height-1] = '#';
	}
	for(int j = 0; j < height; j++) {
		matriz[0][j] = '#';
		matriz[width-1][j] = '#';
	}
	//matriz[x][y] = 'Q';
	for(int k = 0; k <= (Snake->fim)+1; k = (k+1)%Snake->tam) {
	    
	    Ponto s = Snake->vetor[k];
	    if(k == Snake->ini) {
		    matriz[s.x][s.y] = 'M';
        }
        else if(k == Snake->fim){
            matriz[s.x][s.y] = 'F';
        }
        else {
            matriz[s.x][s.y] = 'o';
        }
	}
    Ponto s = frente(Snake);
	if(s.x == prizeX && s.y == prizeY) {
		if(dir == 1){
			enqueue(Snake, s.x, s.y-1, Snake->fim);
		}
		else if(dir == 0){
			enqueue(Snake, s.x-1, s.y, Snake->fim);
		}
		else if(dir == 3){
			enqueue(Snake, s.x, s.y+1, Snake->fim);
		}
		else if(dir == 2){
			enqueue(Snake, s.x+1, s.y, Snake->fim);
		}
		prizeX = rand() % (width-1-shift)+shift;
		prizeY = rand() % (height-1-shift)+shift;
		
	}
	
	for(int j = 0; j < height; j++) {	
		for(int i = 0; i < width; i++) {
			if(j == prizeY && i == prizeX) {
				printf("F");
			}
			else {
				printf("%c", matriz[i][j]);
			}
		} 
		printf("\n");
	}
	usleep(200000);
}

int checkgameOver(Fila *Snake) {
    Ponto s = frente(Snake);
	if(s.x == width || s.x == 0 || s.y == 0 || s.y == height) {
		gameOver = true;
		printf("Game Over\n");
		exit(1);
	}
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
    //printf ("%d %s\n", argc, argv[0]);

	width = atoi(argv[1]);
	height = atoi(argv[2]);
	x = (width-2) / 2;
	y = (height-2) / 2;
	srand(time(NULL));
	prizeX = rand() % (width-1-shift)+shift;
	prizeY = rand() % (height-1-shift)+shift;
	Fila *Snake = create_queue (100);
	enqueue (Snake, x, y, -1);
	//snakeSize = 1;
	char key;
	while(!gameOver) {
		while(!kbhit()) {
			draw(Snake);
			Ponto next = frente(Snake);
			next_x = next.x;
			next_y = next.y;
			printf("%d, %d", next_x, next_y);
			if (key == 'w') {
		    	dequeue(Snake);
			    enqueue (Snake, next_x, next_y-1, Snake->fim);
			    /*colocar a proxima posicao nao a da cabeca*/
				//y--;
				dir = 0;
			} 
			else if (key == 'a') {
		    	Ponto cabeca = dequeue (Snake);
      			//enqueue (Snake, cabeca.x-1, cabeca.y);
			    enqueue (Snake, next_x-1, next_y, Snake->fim);
				//x--;
				dir = 1;
			}
			else if (key == 's') {
				Ponto cabeca = dequeue (Snake);
     			enqueue (Snake, next_x, next_y+1, Snake->fim);
				//y++;
				dir = 2;
			}
			else if (key == 'd') {
				Ponto cabeca = dequeue (Snake);
     			enqueue (Snake, next_x+1, next_y, Snake->fim);
				//x++;
				dir = 3;
			}
			
			checkgameOver(Snake);
		}
		key = getchar();
	}
	
}

