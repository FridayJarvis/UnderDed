#ifndef UNDERDED_RANGEDWEAPON_H
#define UNDERDED_RANGEDWEAPON_H
#include "Weapon.h"


class RangedWeapon : Weapon {
public:
  RangedWeapon(int price, int damage);
  bool attack(std::vector<Enemy>& enemies) override;
};


#endif //UNDERDED_RANGEDWEAPON_H