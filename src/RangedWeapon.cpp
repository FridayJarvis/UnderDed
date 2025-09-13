
#include "RangedWeapon.h"

#include <vector>

class Enemy;

RangedWeapon::RangedWeapon(int price, int damage) : Weapon(price, damage) {
}

bool RangedWeapon::attack(std::vector<Enemy>& enemies) {
  return true;
}

