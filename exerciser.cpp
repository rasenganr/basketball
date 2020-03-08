#include "exerciser.h"

void exercise(connection * C) {
  add_state(C, "NC");
  add_state(C, "VA");
  add_color(C, "LightBlue");
  add_color(C, "Orange");
  add_player(C, 1, 1, "Jerome", "Robinson", 34, 19, 4, 3, 1.7, 0.4);
  add_player(C, 1, 0, "Ky", "Bowman", 29, 14, 5, 3, 1.2, 0.1);
  add_team(C, "BostonCollege", 10, 7, 2, 16);
}
