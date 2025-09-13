//
// Created by Edwin_Jarvis on 13.09.2025.
//

#ifndef UNDERDED_MELEEWEAPON_H
#define UNDERDED_MELEEWEAPON_H
#include "Weapon.h"


class MeleeWeapon : Weapon {
public:
  MeleeWeapon(int price, int damage, int range);
  bool attack() override;

private:
  int range;

};


#endif