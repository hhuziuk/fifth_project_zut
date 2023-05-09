#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
using namespace std;

class Player {
public:
    Player();
    friend ostream& operator<<(ostream& os, const Player& player);
  bool operator<(const Player &other) const;
    Player& operator+=(int value);
    Player& operator-=(int value);
    void setName(const std::string& name);
    std::string getName() const;
    int getMoney() const;
    void addMoney(int amount);
    void loseMoney();

private:
    std::string name;
    int money;
    int wallet;
};

#endif