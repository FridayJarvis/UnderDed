//
// Created by Edwin_Jarvis on 13.09.2025.
//

#include "../include/MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int price, int damage, int range) : Weapon(price, damage), range(range) {
}

bool MeleeWeapon::attack() override {
  return true;
}
