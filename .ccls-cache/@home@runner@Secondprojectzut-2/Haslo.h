#ifndef HASLO_H
#define HASLO_H

#include <string>
#include <vector>

class Haslo {
public:
  void loadWords();
  std::string getRandomWord();

private:
  std::vector<std::string> words;
};

#endif