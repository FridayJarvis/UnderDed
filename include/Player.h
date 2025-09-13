//
// Created by Edwin_Jarvis on 13.09.2025.
//

#ifndef UNDERDED_PLAYER_H
#define UNDERDED_PLAYER_H
#include "Coord.h"
#include "Inventory.h"
#include "Weapon.h"


class Player {
  Coord position;

  int health;
  int speed;

  Inventory inventory;
  Weapon currentWeapon;


};


#endif //UNDERDED_PLAYER_H