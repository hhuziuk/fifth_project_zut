#ifndef GAME_H
#define GAME_H
#include "Haslo.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Game {
public:
  Game();
  void play();
  char readLetter();
  char readChoice();
  int isVowel(char c);
  void textPlayers();

private:
  vector<Player> players;
  int currentPlayer;
  Haslo haslo;
};

#endif