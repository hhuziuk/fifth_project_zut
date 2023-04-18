#include "Player.h"

Player::Player() : money(0), wallet(0) {}

void Player::setName(const std::string &name) {
    this->name = name;
}

std::string Player::getName() const {
    return name;
}

int Player::getMoney() const {
    return money;
}

void Player::addMoney(int amount) {
    money += amount;
}

void Player::loseMoney() {
    money = 0;
}