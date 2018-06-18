#include <curses.h>

struct point {
  int x;
  int y;
};

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

// returns true if the player answers well the riddle
// const is necessary to stop C++ complaining ;)
bool riddle1( int elems, char const answer[] ) {
  mvaddstr(1, 1, "Tu Traductor Universal está abierto para que ingreses la respuesta al acertijo.");
  mvprintw(2, 1, "// Nota: Son %d letras, la primera siempre es mayúscula.", elems);
  mvaddstr(4, 1, "Ingresa el resultado de tu Traductor Universal en la tabla de arcilla blanda.");
  print_rectangle( point{5,1}, point{7,5} );

  // here goes the input of the player
  char playerinput[elems];

  curs_set(1); // making cursor visible again
  echo();      // letting the player see what he inputs
  move(6,2);
  for (int i = 0; i < elems; i++) {
    playerinput[i] = getch();
  }
  curs_set(0); // making cursor invisible again
  noecho();    // from now on the player can't see what he is writing

  bool all_equal = true;
  for (int i = 0; i < elems; i++) {
    if(answer[i] != playerinput[i]) {
      all_equal = false;
    }
  }

  if( all_equal ){
    mvaddstr(9, 1, "¡Respuesta correcta!");
    getch();
    return true;
  } else {
    mvaddstr(9, 1, "NOP, lo siento.");
    getch();
    return false;
  }
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

  bool done = false;
  while( !done ) {
    clear();
    done = riddle1( 3, "Alf" );
  }

  clear();
  mvaddstr(1, 1, "Bye! :D");
  getch();

  endwin(); // closing window

  return 0;
}
