#include <curses.h>
#include "lib/randutils.hh"

/*
 clang++ -lcurses -Wall -Werror -std=c++11 group5-tetris.cc -o group5-tetris
*/

struct pos {
  int x;
  int y;
};

enum colors {
  color_player=1, color_player_alt, silla, background, foreground
};

enum orientation {
  east, south, west, north
};

enum piece_kind {
  kind_T, kind_L, kind_Square, kind_S, kind_I
};

struct piece {
  pos         positi;
  piece_kind  kind;
  pos         body[4];
};

void printpos(pos p, int c, colors uncolor) {
  color_set(uncolor, NULL);
  mvaddch( p.x, 2*p.y, c );
  mvaddch( p.x, 2*p.y+1, c );
}

short color_from_RGB(char r, char g, char b) {
    return (r*36 + g*6 + b*1) + 16;
}

short grey_from_24(char g) {
    return 216 + g + 16;
}

void little_square(int x1, int x2, int y1, int y2) {
  mvaddch(x1, y1, ACS_ULCORNER);
  mvaddch(x1, y1+y2-1, ACS_URCORNER);
  mvaddch(x1+x2-1, y1, ACS_LLCORNER);
  mvaddch(x1+x2-1, y1+y2-1, ACS_LRCORNER);

  for(int i=1; i<y2-1; i++) {
    mvaddch(x1,    y1+i, ACS_HLINE);
    mvaddch(x1+x2-1, y1+i, ACS_HLINE);
  }
  for(int i=1; i<x2-1; i++) {
    mvaddch(x1+i, y1,      ACS_VLINE);
    mvaddch(x1+i, y1+y2-1, ACS_VLINE);
  }
}

void print_silla(piece p) {
  pos po = p.positi;
  pos *body = p.body;
  for (int i = 0; i < 4; i++) {
    printpos(pos{po.x+body[i].x, po.y+body[i].y}, ' ', silla);
  }
}

pos rotated_pos(pos p) {
  return pos{p.y, -p.x};
}

void printtab(int tab[20][12]) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 12; j++) {
      move(i,2*j);
      switch(tab[i][j]) {
        case 0: color_set(background, NULL); break;
        case 1: color_set(foreground, NULL); break;
      }
      addstr("  ");
    }
  }
}

bool valid_new_pos(piece p, int tab[20][12]) {
  pos pc = p.positi;
  pos *b = p.body;
  for (int i = 0; i < 4; i++) {
    int x = pc.x + b[i].x;
    int y = pc.y + b[i].y;
    //mvprintw(22, 22, "%d", y);
    if(x>=0 && (tab[x][y] == 1 || x>=20 || y>=12 || y<0)) {
      return false;
    }
  }
  return true;
}

piece newposition(piece p, int c, int tab[20][12]) {
  piece newp = p;
  bool check_new = true;
  switch(c) {
    case KEY_LEFT:  newp.positi.y--; break;
    case KEY_RIGHT: newp.positi.y++; break;
    case KEY_DOWN:  newp.positi.x++; check_new = false; break;
    case KEY_UP: 
      if(p.kind != kind_Square) {
        for (int i = 0; i < 4; i++) {
          newp.body[i] = rotated_pos(newp.body[i]);
        }
      }
      break;
  }

  if(check_new && !valid_new_pos(newp, tab)) {
    return p;
  } else {
    return newp;
  }
}

bool piece_on_top(piece p, int tab[20][12]) {
  pos pc = p.positi;
  pos *b = p.body;
  for (int i = 0; i < 4; i++) {
    int x = pc.x + b[i].x;
    int y = pc.y + b[i].y;
    //mvprintw(22, 22, "%d", y);
    if(tab[x][y] == 1 || x>=20) {
      return true;
    }
  }
  return false;
}

bool remove_row_if_complete(int tab[20][12]) {
  int some_complete = false;
  for (int i = 19; i >= 0; i--) {
    bool complete = true;
    for (int j = 0; j < 12; j++) {
      if(tab[i][j] != 1) {
        complete = false;
      }
    }
    if(complete) {
      for(int ii = i; ii>=1; ii--) {
        for (int j = 0; j < 12; j++) {
          tab[ii][j] = tab[ii-1][j];
        }
      }
      i++;
      some_complete = true;
    }
  }
  return some_complete;
}

piece change_body(piece p, pos body[4]) {
  piece newpiece = p;
  for (int i = 0; i < 4; i++) {
    newpiece.body[i] = body[i];
  }
  return newpiece;
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

  init_pair(color_player,     grey_from_24(0), color_from_RGB(5,5,2));
  init_pair(color_player_alt, grey_from_24(0), color_from_RGB(2,5,5));
  init_pair(silla,            grey_from_24(0), color_from_RGB(5,0,5));
  init_pair(background,       grey_from_24(23), grey_from_24(0));
  init_pair(foreground,       grey_from_24(23), color_from_RGB(0,5,0));

  //little_square(2, 3, 1, 8);
  //getch();
  //mvaddch(3, 5, 'a');

  randutils::mt19937_rng rng;

  pos player;
  player.x = 3;
  player.y = 14;

  //nodelay(stdscr, true);
  printpos( player, ' ', color_player );
  nodelay(stdscr, true);

  pos body[7][4] = {
    {{0,0},{-1,0},{ 0,-1},{ 0, 1}},  // T
    {{0,0},{-1,0},{ 1, 0},{ 2, 0}},  // I
    {{0,0},{-1,0},{ 0,-1},{-1, 1}},  // S
    {{0,0},{-1,0},{ 0, 1},{-1,-1}},  // S (inverted)
    {{0,0},{-1,0},{-1, 1},{ 0, 1}},  // Square
    {{0,0},{-1,0},{ 1, 0},{ 1,-1}},  // L (inverted)
    {{0,0},{-1,0},{ 1, 0},{ 1, 1}}   // L
  };
  piece_kind body_kind[7] = {kind_T, kind_I, kind_S, kind_S, kind_Square, kind_L, kind_L};
  int rndbody = rng.uniform(0, 6);

  piece apiece = change_body(piece{pos{2, 6}, body_kind[rndbody]}, body[rndbody]);
  bool alive = true;
  int tab[20][12];

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 12; j++) {
      tab[i][j] = 0;
    }
  }

  //tab[19][6] = 1;

  bool color1 = true;
  bool quit = false;
  int frame = 1;
  int speed = 20; // the bigger the slower
  while( !quit ) {
    int c = getch();
    switch(c) {
      case KEY_LEFT:  player.y--; break;
      case KEY_RIGHT: player.y++; break;
      case KEY_UP:    player.x--; break;
      case KEY_DOWN:  player.x++; break;
      case 'q': quit = true; break;
      default: color1 = frame%5==0 ? !color1 : color1;
    }

    clear();

    if(alive) {
      piece newpos = newposition(apiece, c, tab);

      // checking if it's time for the piece to fall a position
      // (it shouldn't fall further if newpos has already fell)
      if( frame%speed == 0 && newpos.positi.x == apiece.positi.x ) {
        newpos.positi.x++;
      }

      //mvprintw(22, 2, "%d %d", newpos.positi.x, newpos.positi.y);
      if(piece_on_top(newpos, tab)) {
        alive = false;
        pos p = newpos.positi;
        pos *b = newpos.body;
        for (int i = 0; i < 4; i++) {
          tab[p.x+b[i].x-1][p.y+b[i].y] = 1;
        }
      }

      apiece = newpos;
    } else {
      // put new piece at the top of the game
      rndbody = rng.uniform(0, 6);

      apiece.positi = pos{2,5};
      apiece.kind = body_kind[rndbody];
      apiece = change_body(apiece, body[rndbody]);

      if(valid_new_pos(apiece, tab)) {
        alive = true;
      } else {
        quit = true;
      }
    }
    bool removed = remove_row_if_complete(tab);
    if(removed && speed>1) {
      speed--; // this increases the speed of the game
    }

    printtab(tab);
    if(alive) {
      print_silla(apiece);
    }

    if(color1) {
      printpos( player, ' ', color_player );
    } else {
      printpos( player, ' ', color_player_alt );
    }
    napms(20);
    frame++;
  }

  //nodelay(stdscr, false); // activating blocking getch
  //getch(); // waiting for user to press a key

  endwin(); // closing window

  return 0;
}
