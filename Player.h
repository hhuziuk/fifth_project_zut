#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player();
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