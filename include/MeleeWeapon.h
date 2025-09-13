#ifndef UNDERDED_MELEEWEAPON_H
#define UNDERDED_MELEEWEAPON_H
#include <vector>

#include "Weapon.h"


class Enemy;

class MeleeWeapon : Weapon {
public:
  MeleeWeapon(int price, int damage, int range);
  bool attack(std::vector<Enemy>& enemies) override;

private:
  int range;

};


#endif