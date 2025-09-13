//
// Created by Edwin_Jarvis on 13.09.2025.
//

#ifndef UNDERDED_PLAYER_H
#define UNDERDED_PLAYER_H
#include <memory>

#include "Coord.h"
#include "Inventory.h"
#include "Shield.h"
#include "Weapon.h"


class Player {
  Coord position;

  int health;
  int speed;

  Inventory inventory;
  std::unique_ptr<Weapon> currentWeapon;

public:
  Player(Coord& position, Inventory& inventory, std::unique_ptr<Weapon> currentItem, int health, int speed);

  bool attack(Weapon& weapon);
  bool useShield(Shield& shield);
  void move(Coord& delta);
  void loseHealth(int damage);
  void changeWeapon(std::unique_ptr<Weapon> weapon);

  bool addItem(Item& item);
  bool removeItem(Item& item);

  int getHealth();

  Coord &getPosition();
  int getSpeed();
  Inventory& getInventory();

  std::unique_ptr<Weapon> getCurrentWeapon();

  void setHealth(int health);
  void setPosition(Coord &position);

  void setPosition(int x, int y);

  void setSpeed(int speed);

  void setBulletAmount(int bulletAmount);

  void setAidKitAmount(int aidKitAmount);

  void setItem(Item &item);

  void setCurrentWeapon(Weapon& currentWeapon);
};


#endif //UNDERDED_PLAYER_H