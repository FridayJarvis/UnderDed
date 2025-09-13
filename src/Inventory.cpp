#include "../include/Inventory.h"

Inventory::Inventory(int money, int bulletAmount, int aidKitAmount, std::vector<Item>& items) : items(items) {
  this->money = money;
  this->bulletAmount = bulletAmount;
  this->aidKitAmount = aidKitAmount;
}

void Inventory::add(Item& item) {
}

void Inventory::clear(Item& item) {
}

int Inventory::getBulletAmount() {
}

int Inventory::getAidKitAmount() {
}

int Inventory::getMoney() {
}

void Inventory::setBulletAmount(int bulletAmount) {
}

void Inventory::setAidKitAmount(int aidKitAmount) {
}

void Inventory::setMoney(int money) {
}
