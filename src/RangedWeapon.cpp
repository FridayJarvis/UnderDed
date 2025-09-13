//
// Created by Edwin_Jarvis on 13.09.2025.
//

#include "../include/RangedWeapon.h"

RangedWeapon::RangedWeapon(int price, int damage) : Weapon(price, damage) {
}

bool RangedWeapon::attack() override {
  return true;
}

