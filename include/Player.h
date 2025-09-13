
#ifndef UNDERDED_PLAYER_H
#define UNDERDED_PLAYER_H
#include <memory>

#include "Coord.h"
#include "Inventory.h"
#include "Shield.h"
#include "Weapon.h"
class Enemy;
class Weapon;

class Player {
  Coord pos;

  int health;
  int speed;

  Inventory inventory;
  std::unique_ptr<Weapon> currentWeapon;

public:
  Player(Coord& pos, Inventory& inventory, std::unique_ptr<Weapon> currentWeapon, int health, int speed);

  bool attack(std::unique_ptr<Weapon> weapon, std::vector<Enemy>& enemies);

  bool useShield(Shield &shield);

void move(Coord&& delta);

void loseHealth(int damage);

void changeWeapon(std::unique_ptr<Weapon> weapon);

bool addItem(Item &item);

bool removeItem(Item &item);

int getHealth();

Coord& getPosition();

int getSpeed();

Inventory& getInventory();

std::unique_ptr<Weapon> getCurrentWeapon();

void setHealth(int health);

void setPosition(Coord& pos);

void setPosition(int x, int y);

void setSpeed(int speed);

void setBulletAmount(int bulletAmount);

void setAidKitAmount(int aidKitAmount);

void setItem(Item& item);

void setCurrentWeapon(Weapon& currentWeapon);

};


#endif //UNDERDED_PLAYER_H