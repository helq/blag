#include <curses.h>

/*
 clang++ -lcurses -Wall -Werror -std=c++11 group6-tetris.cc -o group6-tetris
*/

struct pair {
  int x;
  int y;
};

void little_rectanglishish(int x1, int y1, int x2, int y2) {
  for(int i=0; i<x2-x1+1; i++) {
    mvaddch(y1, x1+i, ACS_HLINE);
    mvaddch(y2, x1+i, ACS_HLINE);
  }
  for(int i=1; i<y2-y1; i++) {
    mvaddch(y1+i, x1, ACS_VLINE);
    mvaddch(y1+i, x2, ACS_VLINE);
  }
  mvaddch(y1, x1, ACS_ULCORNER);
  mvaddch(y1, x2, ACS_URCORNER);
  mvaddch(y2, x1, ACS_LLCORNER);
  mvaddch(y2, x2, ACS_LRCORNER);
}

void print_lazy(pair p) {
  mvaddch(p.y, 2*p.x, ' ');
  mvaddch(p.y, 2*p.x+1, ' ');
}

short color_from_RGB(char r, char g, char b) {
    return (r*36 + g*6 + b*1) + 16;
}

short grey_from_24(char g) {
    return 216 + g + 16;
}

int main()
{
  // Configurations for PDCurses in windows (this doesn't affect regular ncurses in linux)
  ttytype[0] = 35;  ttytype[1] = 45; // 35 to 45 lines height
  ttytype[2] = 80;  ttytype[3] = (unsigned char)130; // 80 to 130 characters width

  // Initializing window to print in
  initscr();   // starting screen
  cbreak();
  noecho();    // consume characters without showing them in screen
  curs_set(0); // setting cursor as invisible
  keypad(stdscr, true); // allowing ncurses to convert press keys into curses representation (useful for KEY_UP)
  start_color(); // asking ncurses to use colors
  init_pair( 1, grey_from_24(0), color_from_RGB(5,5,5) );
  init_pair( 2, grey_from_24(0), color_from_RGB(1,1,5) );
  init_pair( 3, grey_from_24(0), color_from_RGB(5,1,3) );

  clear();     // cleanning screen

  //mvaddch(3, 20, ACS_ULCORNER);
  //mvaddch(3, 21, ACS_HLINE);
  //mvaddch(3, 22, ACS_URCORNER);
  //mvaddch(4, 20, ACS_LLCORNER);
  //mvaddch(4, 21, ACS_HLINE);
  //mvaddch(4, 22, ACS_LRCORNER);
  //mvaddch(0, 0, 'R');

  //little_square(5, 8, 25, 20);
  //little_square(2, 4, 10, 15);
  //mvaddch(15, 5, ACS_PLUS);

  pair player;
  player.x = 5;
  player.y = 5;
  pair cc;
  cc.x = 12;
  cc.y = 3;

  color_set(3, NULL);
  print_lazy(player);

  while(true) {
    int variable = getch();
    switch(variable) {
      case KEY_UP:    player.y--; break;
      case KEY_DOWN:  player.y++; break;
      case KEY_LEFT:  player.x--; break;
      case KEY_RIGHT: player.x++; break;
    }
    cc.y++;
    clear();
    color_set(2, NULL);
    pair ccc1 = cc;
    ccc1.x--;
    pair ccc2 = cc;
    ccc2.x++;
    pair ccc3 = cc;
    ccc3.y--;
    print_lazy(cc);
    print_lazy(ccc1);
    print_lazy(ccc2);
    print_lazy(ccc3);
    color_set(3, NULL);
    print_lazy(player);
  }

  getch();

  endwin(); // closing window

  return 0;
}
