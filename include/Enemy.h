#ifndef UNDERDED_ENEMY_H
#define UNDERDED_ENEMY_H
#include "Coord.h"

class Enemy {
public:
  Enemy() = default;
  Enemy(Coord pos, int damage, int health) : position(pos), damage(damage), health(health) {}

  Coord& getPos() { return position; }
  void setPosition(int x, int y) { position.x = x; position.y = y; }

  int getDamage() const { return damage; }
  int getHealth() const { return health; }
  void loseHealth(int d) { if (d > 0) health -= d; }

private:
  Coord position{0,0};
  int damage = 1;
  int health = 2;
};

#endif
