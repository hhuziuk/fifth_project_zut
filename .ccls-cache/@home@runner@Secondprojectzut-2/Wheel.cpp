#include "Wheel.h"
#include <cstdlib>
#include <ctime>

int Wheel::spin() {
  srand(time(NULL));
  int i = rand() % 15;
  return wheel[i];
}