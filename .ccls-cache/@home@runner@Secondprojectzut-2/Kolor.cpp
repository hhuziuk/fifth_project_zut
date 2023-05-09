#include "Kolor.h"

std::string Kolor::red(const std::string &text) {
  return "\033[1;31m" + text + "\033[0m";
}

std::string Kolor::blue(const std::string &text) {
  return "\033[1;34m" + text + "\033[0m";
}

std::string Kolor::green(const std::string &text) {
  return "\033[1;32m" + text + "\033[0m";
}