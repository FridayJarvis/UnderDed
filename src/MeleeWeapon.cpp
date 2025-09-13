
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(int price, int damage, int range) : Weapon(price, damage), range(range) {
}

bool MeleeWeapon::attack(std::vector<Enemy>& enemies) {
  return true;
}
