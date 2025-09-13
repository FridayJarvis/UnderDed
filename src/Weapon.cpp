#include "Weapon.h"

class Item;

Weapon::Weapon(int price, int damage):
::Item(price), damage(damage) {
}

int Weapon::getDamage() {
  return damage;
}

void Weapon::setDamage(int damage) {
  this->damage = damage;
}
