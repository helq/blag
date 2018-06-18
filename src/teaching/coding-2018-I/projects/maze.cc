#include <curses.h>
#include "lib/randutils.hh"

struct pos {
  int x;
  int y;
};

short color_from_RGB(char r, char g, char b) {
    return (r*36 + g*6 + b*1) + 16;
}

short grey_from_24(char g) {
    return 216 + g + 16;
}

void print_maze(char maze[][40], int height, int width, pos offset) {
  color_set(3, NULL);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (maze[i][j] == '*') {
        move(offset.x + i, offset.y + 2*j);
        addstr("  ");
      }
    }
  }
}

void printpos(pos p, pos offset, int uncolor) {
  color_set(uncolor, NULL);
  mvaddstr( offset.x + p.x, offset.y + 2*p.y, "  " );
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

  clear();     // cleanning screen

  init_pair(1, grey_from_24(0), color_from_RGB(0,5,0));
  init_pair(2, grey_from_24(0), color_from_RGB(5,0,5));
  init_pair(3, grey_from_24(0), color_from_RGB(5,2,1));
  init_pair(4, grey_from_24(23), grey_from_24(0));
  init_pair(5, grey_from_24(23), color_from_RGB(0,5,0));

  char maze[25][40] = {
    "***************",
    "*i*           *",
    "* ****** **** *",
    "*        *    *",
    "******* *  ****",
    "* *     **    *",
    "* * ** * **** *",
    "* *   *       *",
    "*   * * *******",
    "* *   *       *",
    "************* *"
  };

  pos offset = {2, 5};
  pos player = {1, 1};
  int player_color = 2;

  nodelay(stdscr, true);
  print_maze(maze, 11, 15, offset);
  printpos(player, offset, player_color);

  bool quit = false;
  int frame = 1;
  for(; !quit; frame++) {
    int c = getch();
    pos mov = pos{0, 0};
    switch (c) {
      case KEY_UP:    mov = pos{-1, 0}; break;
      case KEY_DOWN:  mov = pos{1, 0};  break;
      case KEY_LEFT:  mov = pos{0, -1}; break;
      case KEY_RIGHT: mov = pos{0, 1};  break;
      case 'q': quit = true; break;
    }

    // Checking if it is possible to move to the new position
    if( maze[player.x + mov.x][player.y + mov.y] != '*' ) {
      player.x += mov.x;
      player.y += mov.y;
    }

    // Changing colors every 20 frames
    if( frame % 20 == 0 ) {
      player_color = player_color%2 + 1;
    }

    clear();
    print_maze(maze, 11, 15, offset);
    printpos(player, offset, player_color);
    napms(20);
  }

  clear();
  move(1, 1);
  addstr("BYE ;)");

  nodelay(stdscr, false);
  getch();

  endwin(); // closing window

  return 0;
}
