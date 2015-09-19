#include <list>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

class snake {
	private:
		int x, y;
	public:
		snake(int a, int b) {
			x = a;
			y = b;
		}
		int getX() { return x; }
		int getY() { return y; }
};

int main() {
	// Init
	srand ( time(NULL) );
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	timeout(100);

	std::list<snake> snakes;
	std::list<snake>::iterator it;
	bool quit = false;
	int points = 0;
	int dir = 2;
	int food_x = rand() % 80 + 1;
	int food_y = rand() % 24 + 1;
	int ch;

	for(int i = 0; i < 5; i++)	// generate start snake
		snakes.push_front(snake(3+i,3));

	while(!quit) {
	// Input
	ch = getch();
	switch(ch) {
		case KEY_UP:
			dir = 1;
			break;
		case KEY_RIGHT:
			dir = 2;
			break;
		case KEY_DOWN:
			dir = 3;
			break;
		case KEY_LEFT:
			dir = 4;
			break;
		case 'q':
			quit = true;
			break;
	}

	// Logic
	snake logic = snakes.front();
	int x = logic.getX();
	int y = logic.getY();
	if(dir == 1) y--;	// move up
	else if(dir == 2) x++;	// move right
	else if(dir == 3) y++;	// move down
	else if(dir == 4) x--;	// move left

	snakes.push_front(snake(x, y));

	if(x == food_x && y == food_y) {
		food_x = rand() % 80;
			food_y = rand() % 24;
			points++;
	} else
		snakes.pop_back();

	if(y > 24 || x > 80 || y < 0 || x < 0)	// collision with border
		quit = true;

	// Output
	erase();
	mvaddch(food_y,food_x,'X');
	for(it = snakes.begin(); it != snakes.end(); it++) {
		mvaddch((*it).getY(),(*it).getX(),'o');
		if((*it).getY() == y && (*it).getX() == x && it != snakes.begin())	// collision with snake
			quit = true;
	}
	mvprintw(0, 0, "You got %i points. 'q' to quit.\n", points);
	refresh();
	}
	timeout(-1);
	erase();
	mvprintw(0, 0, "You lost and gained a total of %i points.\n", points);
	refresh();
	getch();	// wait for input

	endwin();
	return 0;
}
