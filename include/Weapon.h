#ifndef UNDERDED_WEAPON_H
#define UNDERDED_WEAPON_H
#include <vector>

#include "Enemy.h"
#include "Item.h"


class Weapon : protected Item{
protected:
  int damage;

public:
  Weapon(int price, int damage);

  virtual int getDamage();
  virtual void setDamage(int damage);

  virtual bool attack(std::vector<Enemy>& enemies) = 0;

  virtual ~Weapon() = default;
};


#endif //UNDERDED_WEAPON_H