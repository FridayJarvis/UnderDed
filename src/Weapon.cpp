//
// Created by Edwin_Jarvis on 13.09.2025.
//

#include "../include/Weapon.h"

Weapon::Weapon(int price, int damage)
  : Item(price), damage(damage) {
}

int Weapon::getDamage() {
  return damage;
}

void Weapon::setDamage(int damage) {
  this->damage = damage;
}
