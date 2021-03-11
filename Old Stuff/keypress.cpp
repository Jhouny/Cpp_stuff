#include <ncurses.h>
#include <unistd.h>  /* only for sleep() */


int main() {
	keypad(stdscr, TRUE);
	initscr();
	while(1){
		int ch = getch();
		printw("no key was pressed was pressed: %d\n", ch);
		refresh();
	}
}



