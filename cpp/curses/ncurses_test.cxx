#include <iostream>
#include <ncurses.h>
#include <string>


int main() {
  initscr();
  start_color();
  if (has_colors()) {
    std::cout << "Terminal" << " does support colors!\n\r";
    short R;
    short G;
    short B;
    short color = 0;
    std::cout << COLORS << "\n\r";
    for (; color < COLORS; ++color) {
      color_content(color, &R, &G, &B);
      if (color == COLOR_BLACK) {
        init_pair(color+1, COLOR_WHITE, color);
      } else {
        init_pair(color+1, COLOR_BLACK, color);
      }
      attrset(COLOR_PAIR(color+1));
      printw("%2d: %d,%d,%d\n\r", color, R*255/1000, G*255/1000, B*255/1000);
    }
  }
  getch();
  endwin();
  return 0;
}
