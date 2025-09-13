//
// Created by Edwin_Jarvis on 13.09.2025.
//

#ifndef UNDERDED_RANGEDWEAPON_H
#define UNDERDED_RANGEDWEAPON_H
#include "Weapon.h"


class RangedWeapon : Weapon {
public:
  RangedWeapon(int price, int damage);
  bool attack() override;
};


#endif //UNDERDED_RANGEDWEAPON_H