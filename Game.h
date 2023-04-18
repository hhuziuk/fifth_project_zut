#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
using namespace std;

class Game {
public:
    Game();
    void play();
    char readLetter();
    char readChoice();
    int isVowel(char c);
    void textPlayers();
    void loadWords();
    string getRandomWord();

private:
    vector<Player> players;
    vector<string> words;
    int currentPlayer;
    int wheel[16];
    string has;
};

#endif