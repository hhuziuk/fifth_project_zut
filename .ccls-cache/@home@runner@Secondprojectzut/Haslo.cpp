#include "Haslo.h"
#include <ctime>
#include <fstream>
#include <locale>

void Haslo::loadWords() {
  std::ifstream inFile;
  inFile.open("dane.txt");
  setlocale(LC_CTYPE, "Polish");
  while (!inFile.eof()) {
    std::string s;
    getline(inFile, s);
    words.push_back(s);
  }
  inFile.close();
}

std::string Haslo::getRandomWord() {
  srand(time(NULL));
  if (words.size() > 0) {
    int index = rand() % words.size();
    return words[index];
  }
  return "";
}