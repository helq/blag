#include <curses.h>
//#include <chrono>
//#include <thread>
//#include <iostream>
#include "lib/randutils.hh"

/*
 to compile (linux):
 clang++ -lcurses -Wall -Werror -std=c++11 snake.cc -o snake

 to compile (windows) (could be done with clang too, but it's a little more cumbersome):
 i686-w64-mingw32-g++ -I../../../win/pdcurses-bin -Wall -Werror -static -lpthread -o snake.exe snake.cc ../../../win/pdcurses-bin/pdcurses.a
 i686-w64-mingw32-g++ -I../../../win/pdcurses-bin/old -Wall -Werror -static -lpthread -o snake.exe snake.cc ../../../win/pdcurses-bin/old/pdcurses.a
*/

// TODO: There are a couple of things this game is missing. Some of them are:
// - A new piece of food should never appear in the middle of the snake, that
//   happens right now ocassionally
// - Barriers, some walls, for example, where the snake may collide and die
// - Super food, something to give the snake points (the superfood should stay
//   on screen just for a couple of seconds)
// - Variable difficulty of the game
// - Diffferent "mazes" (different environments where to play)
// - Save automatically highest score
// - Do something when the size of the snake arrives at the max_size, what
//   should be done?

struct point {
  int x;
  int y;
};

enum direction {
  up, down, right, left
};

struct snake {
  int size;
  int max_size;
  point* body;
};

struct game {
  int height;
  int width;
  direction dir;
  snake sn;
  point food;
};

enum color {
  my_black = 1,
  my_white, my_white_bg,
  my_green, my_green_bg,
  my_yellow_bg,
  my_blue_bg
};

// we change `char` for `int` becase ncurses can return a character that is not
// ascii but a control character
direction getdir( direction dir, int c ) {
  switch (c) {
    case 'w': case 'W': case KEY_UP:    return up;
    case 's': case 'S': case KEY_DOWN:  return down;
    case 'a': case 'A': case KEY_LEFT:  return left;
    case 'd': case 'D': case KEY_RIGHT: return right;
  }
  return dir;
}

bool check_died(point newpos, snake sn) {
  for (int i = 0; i < sn.size-1; i++) {
    if (   (newpos.x == sn.body[i].x)
        && (newpos.y == sn.body[i].y)) {
      return true;
    }
  }

  return false;
}

// returns a random point in the space given by height and width
point random_point( int height, int width ) {
  randutils::mt19937_rng rng;
  int x = rng.uniform(0, height-1);
  int y = rng.uniform(0, width-1);
  return point{x,y};
}

// TODO: This is implicitly changing the game internals, :(, it should copy
// them
bool newpos_snake( game &g ) {
  int h = g.height;
  int w = g.width;

  // Changing position of snake's head
  point oldpos = g.sn.body[0];
  point newpos = oldpos;
  switch (g.dir) {
    case up:    newpos.x = (g.sn.body[0].x+h-1) % h; break;
    case down:  newpos.x = (g.sn.body[0].x  +1) % h; break;
    case right: newpos.y = (g.sn.body[0].y  +1) % w; break;
    case left:  newpos.y = (g.sn.body[0].y+w-1) % w;
  }

  // if the new position (head) for the snake collides with its body, then the
  // snake has died
  if( check_died(newpos, g.sn) ) {
    return true;
  }

  // checking if the new position for the head coincides with the piece of food
  if ((newpos.x == g.food.x) && (newpos.y == g.food.y)) {
    // generating new position for food particle
    g.food = random_point( g.height, g.width );

    // the snake had just eaten a piece of food, congratulations
    g.sn.size += 1;
  }

  g.sn.body[0] = newpos;

  // Changing position of the rest of the body (the body must follow the old
  // position of the head)
  for (int i=1; i<g.sn.size; i++) {
    point tmp = g.sn.body[i];
    g.sn.body[i] = oldpos;
    oldpos = tmp;
  }

  return false;
}

bool check_newdir(direction olddir, direction newdir) {
  return !( ( (olddir==up)    && (newdir==down)  )
         || ( (olddir==down)  && (newdir==up)    )
         || ( (olddir==right) && (newdir==left)  )
         || ( (olddir==left)  && (newdir==right) )
         );
}

// TODO: do NOT change the internal state of the game in this function, but for
// that you shouldn't use naked pointers
bool next_step(game &g, int c) {
  direction newdir = getdir( g.dir, c ); // finding new direction
  // checking if the new directions is a valid direction
  if( check_newdir( g.dir, newdir ) ) {
    g.dir = newdir;
  }
  // moving head to new direction, returns true if the last position is not
  // possible, ie, the snake died
  return newpos_snake( g );
}

void print_rectangle(point a, point b) {
  mvaddch(a.x, a.y, ACS_ULCORNER); // upper-left  corner character
  mvaddch(a.x, b.y, ACS_URCORNER); // upper-right corner character
  mvaddch(b.x, b.y, ACS_LRCORNER); // lower-right corner character
  mvaddch(b.x, a.y, ACS_LLCORNER); // lower-left  corner character
  for (int i = a.x+1; i < b.x; i++) {
    mvaddch(i, a.y, ACS_VLINE); // vertical line character
    mvaddch(i, b.y, ACS_VLINE);
  }
  for (int i = a.y+1; i < b.y; i++) {
    mvaddch(a.x, i, ACS_HLINE); // horizontal line character
    mvaddch(b.x, i, ACS_HLINE);
  }
}

// Takes 3 numbers between 0 and 5 (inclusive) and returns the number a number
// that can be inputed into init_pair.
// R is for Red
// G is for Green
// B is for Blue
// There are in total 6*6*6 different possible colors
short color_from_RGB(char r, char g, char b) {
    return (r*36 + g*6 + b*1) + 16;
}

// Takes a single number between 0 and 23 (inclusive), where 0 is black and 23
// is black.
// The result of this function should be used inside a `init_pair` call.
short grey_from_24(char g) {
    return 216 + g + 16;
}

void print_square(point p, point offset, color c) {
  int x =   p.x + offset.x + 1;
  int y = 2*p.y + offset.y + 1;

  color_set(c, NULL);
  move(x, y);
  addstr("  ");
  color_set(my_white, NULL);
}

void print_snake(snake sn, point offset) {
  print_square(sn.body[0], offset, my_white_bg);

  for (int i = 1; i < sn.size; i++) {
    print_square(sn.body[i], offset, my_blue_bg);
  }
}

void print_food(point food, point offset) {
  print_square(food, offset, my_yellow_bg);
}

void print_help_text(int x, int y) {
  color_set(my_green, NULL);
  mvaddstr(x,   y, "Move with arrow keys");
  mvaddstr(x+1, y, "To quit press 'q'");
  mvaddstr(x+2, y, "To pause press 'p'");
}

void print_score_box(game g, point offset) {
  int center = offset.y + g.width;
  int points = g.sn.size-6;
  mvprintw(1, center, "%d", points);
  int lenscore = 0;
  int p = points;
  do {
    p = p / 10;
    lenscore += 1;
  } while(p != 0);
  print_rectangle(point{0,center-2}, point{2,center+1+lenscore});
}

void print_game(game g) {
  point offset = {3,6};

  point end = {
      g.height + offset.x + 1,
    2*g.width  + offset.y + 1
  };

  // Printing rectangle in which the game sets
  attrset(A_BOLD);
  color_set(my_white, NULL);
  print_rectangle(offset, end);

  // Printing snake
  print_snake(g.sn, offset);

  // Printing food
  print_food(g.food, offset);

  // Printing help text
  print_help_text(end.x+2, offset.y+1);

  // Printing score
  print_score_box(g, offset);
}

snake create_snake(int head_x, int head_y, int size, int max_size) {
  snake sn = {size, max_size, nullptr};
  point* body = new point[max_size];
  sn.body = body;

  for (int i = 0; i < size; i++) {
    body[i].x = head_x;
    body[i].y = head_y-i;
  }

  return sn;
}

//using std::this_thread::sleep_for;
//using std::chrono::milliseconds;

void decreate_snake(snake sn) {
  delete[] sn.body;
}

int main()
{
  game g = { 23, 35, right, create_snake(10, 10, 6, 200), random_point(23, 35) };

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

  // Setting color pairs
  short black = grey_from_24(0);
  init_pair(my_black,     black,                 black                );
  init_pair(my_white,     grey_from_24(23),      black                );
  init_pair(my_white_bg , black,                 grey_from_24(21)     );
  init_pair(my_green,     color_from_RGB(2,3,1), black                );
  init_pair(my_green_bg , black,                 color_from_RGB(2,3,1));
  init_pair(my_yellow_bg, black,                 color_from_RGB(5,4,1));
  init_pair(my_blue_bg,   black,                 color_from_RGB(1,1,5));
  // setting background default color as black
  wbkgd(stdscr, COLOR_PAIR(my_black));

  clear();     // cleanning screen

  nodelay(stdscr, true); // deactivating blocking getch

  bool quit = false;
  bool died = false;
  while( !quit && !died ) {
    int c = getch();

    // if 'q' was pressed, then it's time to end the game
    switch (c) {
      case 'q': quit = true; break;
      case 'p': 
        clear();
        mvaddstr(2, 2, "Game paused, press any key to continue");
        nodelay(stdscr, false); // activating blocking getch
        getch(); // waiting for user to press a key
        nodelay(stdscr, true);
        break;
    }

    // moving game one step further based on the character pressed (or not) by
    // the user. Returns `true` if the snake ate itself
    died = next_step(g, c);

    // printing new state of the game
    clear();
    print_game(g);
    //refresh();
    //resize_term(30,20);

    // consuming all characters in buffer before asking for a new one
    //while (getch() != ERR);

    // You could use this and not sleep_for milliseconds line, but I prefer to use
    // sometimes the standard libraries, thought it's not necessary here
    napms(50);
    //sleep_for( milliseconds(50) );
  }

  if( died && !quit ) {
    nodelay(stdscr, false); // activating blocking getch
    getch(); // waiting for user to press a key
  }

  endwin(); // closing window

  decreate_snake(g.sn);
  return 0;
}
