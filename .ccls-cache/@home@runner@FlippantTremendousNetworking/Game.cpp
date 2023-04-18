#include "Game.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cassert>
#include <locale>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

Game::Game() : currentPlayer(0), wheel{-1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000} {
    players.resize(3);
    players[0].setName("Bryanusz");
    players[1].setName("Jessica ");
    players[2].setName("Nepomucen");
    loadWords();
}

void Game::play() {
    int i;
    string has = getRandomWord();
    string proba;
    char literka;
    int n = has.size();
    int maska[100];
    int suma = 0;
    int zgadl = 0;
    int sa_spolgloski = 0;
    int kwota = 0;
    char wybor;

    for (i = 0; i < n; i++) {
        if (has[i] == ' ') {
            maska[i] = 0;
        } else {
            maska[i] = 1;
        }
    }

    do {
        cout << "\033[47m" << "\033[31m";
        for (i = 0; i < n; i++) {
            if (maska[i] == 1) {
                cout << ".";
            } else {
                cout << has[i];
            }
        }
        cout << "\033[0m" << endl;

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
            for (auto& c : proba) {
                c = toupper(c);
            }
            if (has == proba) {
                cout << endl << " !!!!!!!!!! =======   WYGRANA ========== !!!!!!!!!!!!!" << endl;
                players[currentPlayer].addMoney(players[currentPlayer].getMoney());
                break;
            } else {
                currentPlayer = (currentPlayer + 1) % 3;
                suma = 1;
                cout << endl << " !!!!!!!!!! =======   ZLE ========== !!!!!!!!!!!!!" << endl;
                cout << endl << "=================================================" << endl;
                continue;
            }
        }

        srand(time(NULL));
        string rezultat = "";
        i = rand() % 15;
        if (wheel[i] == 0) {
            rezultat = "Strata kolejki";
        }
        if (wheel[i] == -1) {
            rezultat = "Bankrut";
        }
        if (rezultat != "") {
            cout << "\033[1;31m" << rezultat << "\033[0m" << endl;
        } else {
            cout << "\033[1;34m" << wheel[i] << "\033[0m" << endl;
            kwota = wheel[i];
        }

        if ((wheel[i] == 0) || (wheel[i] == -1)) {
            if (wheel[i] == -1) {
                players[currentPlayer].loseMoney();
            }
            currentPlayer = (currentPlayer + 1) % 3;
            suma = 1;
            cout << endl << "=================================================" << endl;
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
            cout << endl << players[currentPlayer].getName() << "\033[1;32m " << players[currentPlayer].getMoney() << "\033[0m";
        } else {
            cout << "Zle!";
            currentPlayer = (currentPlayer + 1) % 3;
            cout << endl << "=================================================" << endl;
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
            cout << "\033[1;34m";
        }
        cout << players[i].getName() << "\t" << players[i].getMoney() << "\n";
        cout << "\033[0m";
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
    for (auto& c : letter) // & запамітовує зміни в циклі & - посилання
        c = toupper(c);
    return letter[0];
}

char Game::readChoice() {
    char choice;
    choice = readLetter();
    while (choice != '1' && choice != '2') {
        cout << endl << "Виберіть [1-2]: ";
        cin >> choice;
    }
    return choice;
}

void Game::loadWords() {
    ifstream inFile;
    inFile.open("dane.txt");
    setlocale(LC_CTYPE, "Polish");
    while (!inFile.eof()) {
        string s;
        getline(inFile, s);
        words.push_back(s);
    }
    inFile.close();
}

string Game::getRandomWord() {
    srand(time(NULL));
    if (words.size() > 0) {
        int index = rand() % words.size();
        return has = words[index];
    }
    return "";
}