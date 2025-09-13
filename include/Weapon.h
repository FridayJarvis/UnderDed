//
// Created by Edwin_Jarvis on 13.09.2025.
//

#ifndef UNDERDED_WEAPON_H
#define UNDERDED_WEAPON_H
#include "Enemy.h"
#include "Item.h"


class Weapon : protected Item{
protected:
  int damage;

public:
  Weapon(int price, int damage);

  virtual int getDamage();
  virtual void setDamage(int damage);

  virtual bool attack() = 0;

  virtual ~Weapon() = default;
};


#endif //UNDERDED_WEAPON_H