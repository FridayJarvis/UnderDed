#ifndef UNDERDED_PLAYER_H
#define UNDERDED_PLAYER_H

#include "Coord.h"
#include "Inventory.h"
#include <memory>

class Weapon;

class Player {
public:
  Player() = default;

  Coord& getPosition() { return position; }
  void setPosition(Coord& pos) { position = pos; }
  void setPosition(int x, int y) { position.x = x; position.y = y; }

  int getHealth()  { return health; }
  void setHealth(int h) { health = h; if (health < 0) health = 0; if (health > 10) health = 10; }
  void loseHealth(int dmg) { if (dmg > 0) setHealth(health - dmg); }

  Inventory& getInventory() { return inventory; }

  int  getCurrentWeaponSlot()  { return currentWeaponSlot; }
  void setCurrentWeaponSlot(int slot);
  void unlockWeaponSlot(int slot);

private:
  Coord position{0,0};
  int health = 10;

  Inventory inventory;

  int currentWeaponSlot = 1; // 1..3
  bool owned[4] = {false, true, false, false}; // fists=true
};

#endif
