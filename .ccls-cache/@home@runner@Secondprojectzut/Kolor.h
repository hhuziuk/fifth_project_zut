#ifndef KOLOR_H
#define KOLOR_H

#include <string>

class Kolor {
public:
  static std::string red(const std::string &text);
  static std::string blue(const std::string &text);
  static std::string green(const std::string &text);
};

#endif