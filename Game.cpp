#include "Game.h"
#include "Haslo.h"
#include "Kolor.h"
#include "Wheel.h"
#include <cassert>
#include <cctype>
#include <cmath>   
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <locale>

using namespace std;

ostream& operator<<(ostream& os, const Player& player) {
    os << player.getName() << "\t" << player.getMoney();
    return os;
}

Player& Player::operator+=(int value) {
    money += value;
    return *this;
}

Player& Player::operator-=(int value) {
    money -= value;
    return *this;
}

bool operator== (const Player& player1, const Player& player2){
  return player1.getMoney() == player2.getMoney() && player1.getName() == player2.getName();
}

bool Player::operator<(const Player &other) const {
  return money < other.money;
}

Game::Game() : currentPlayer(0) {
  players.resize(3);
  players[0].setName("Bryanusz");
  players[1].setName("Jessica ");
  players[2].setName("Nepomucen");
  haslo.loadWords();
}

void Game::play() {
  int i;
  string has = haslo.getRandomWord();
  string proba;
  char literka;
  int n = has.size();
  int maska[100];
  int suma = 0;
  int zgadl = 0;
  int sa_spolgloski = 0;
  int kwota = 0;
  char wybor;

  Wheel wheel;

  for (i = 0; i < n; i++) {
    if (has[i] == ' ') {
      maska[i] = 0;
    } else {
      maska[i] = 1;
    }
  }

  do {
    cout << Kolor::red("");
    for (i = 0; i < n; i++) {
      if (maska[i] == 1) {
        cout << ".";
      } else {
        cout << has[i];
      }
    }
    cout << Kolor::red("") << endl;

    sa_spolgloski = 0;
    kwota = 0;
    for (i = 0; i < n; i++) {
      if ((!isVowel(has[i])) && (maska[i])) {
        sa_spolgloski = 1;
        break;
      }
    }

    if (sa_spolgloski) {
      cout << " -- Spolgloski sa --" << endl;
    }

    textPlayers();

    cout << "1. zgaduj haslo" << endl;
    cout << "2. krecenie kolem" << endl;

    wybor = readChoice();

    if (wybor == '1') {
      cout << "Podaj haslo" << endl;
      getline(cin >> ws, proba);
      for (auto &c : proba) {
        c = toupper(c);
      }
      if (has == proba) {
        cout << endl
             << " !!!!!!!!!! =======   WYGRANA ========== !!!!!!!!!!!!!"
             << endl;
        players[currentPlayer] += players[currentPlayer].getMoney();
        break;
      } else {
        currentPlayer = (currentPlayer + 1) % 3;
        suma = 1;
        cout << endl
             << " !!!!!!!!!! =======   ZLE ========== !!!!!!!!!!!!!" << endl;
        cout << endl
             << "=================================================" << endl;
        continue;
      }
    }

    i = wheel.spin();
    if (i == 0) {
      cout << Kolor::red("Strata kolejki") << endl;
    } else if (i == -1) {
      cout << Kolor::red("Bankrut") << endl;
    } else {
      cout << Kolor::blue(to_string(i)) << endl;
      kwota = i;
    }

    if ((i == 0) || (i == -1)) {
      if (i == -1) {
        players[currentPlayer] -= players[currentPlayer].getMoney();
      }
      currentPlayer = (currentPlayer + 1) % 3;
      suma = 1;
      cout << endl
           << "=================================================" << endl;
      continue;
    }

    cout << players[currentPlayer].getName() << ": Podaj litere" << endl;
    literka = readLetter();
    zgadl = 0;

    if (isVowel(literka)) {
      cout << "samogloska";
    } else {
      cout << "spolgloska";
    }
    cout << endl;

    for (i = 0; i < n; i++) {
      if ((has[i] == literka) && (maska[i] == 1)) {
        maska[i] = 0;
        zgadl++;
      }
    }

    if (zgadl) {
      cout << "OK";
      players[currentPlayer].addMoney(kwota * zgadl);
      cout << endl
           << players[currentPlayer].getName() << Kolor::green(" ")
           << players[currentPlayer].getMoney();
    } else {
      cout << "Zle!";
      currentPlayer = (currentPlayer + 1) % 3;
      cout << endl
           << "=================================================" << endl;
      suma = 1;
      continue;
    }

    cout << endl;
    suma = 0;
    for (i = 0; i < n; i++) {
      suma += maska[i];
    }
  } while (suma);

  cout << "BRAWO!";
  textPlayers();
}

void Game::textPlayers() {
  int i;
  cout << "\n";
  for (i = 0; i < 3; i++) {
    if (i == currentPlayer) {
      cout << Kolor::blue("");
    }
    cout << players[i] << '\n';
    cout << Kolor::red("");
  }
  cout << "\n";
}

int Game::isVowel(char c) {
  if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
      c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y')
    return 1;
  else
    return 0;
}

char Game::readLetter() {
  string letter;
  cin >> letter;
  while (letter.length() != 1) {
    cout << endl << "Type a single letter and press <enter>: ";
    cin >> letter;
  }
  for (auto &c : letter)
    c = toupper(c);
  return letter[0];
}

char Game::readChoice() {
  char choice;
  choice = readLetter();
  while (choice != '1' && choice != '2') {
    cout << endl << "Wybierz [1-2]: ";
    cin >> choice;
  }
  return choice;
}