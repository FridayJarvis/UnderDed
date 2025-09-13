#ifndef UNDERDED_ENEMY_H
#define UNDERDED_ENEMY_H
#include <utility>

#include "Coord.h"


class Enemy {
  Coord pos;

  int damage;
  int health;
  int speed;
  int rangeOfVisibility;

  bool playerDetected;

  std::pair<int, int> rangeOfX;
  std::pair<int, int> rangeOfY;

public:
  Enemy(Coord& pos, std::pair<int, int>& rangeOfX, std::pair<int, int>& rangeOfY,
    int damage, int health, int speed, int rangeOfVisibility, bool playerDetected);

  Enemy(Coord&& pos, std::pair<int, int>&& rangeOfX, std::pair<int, int>&& rangeOfY,
    int damage, int health, int speed, int rangeOfVisibility, bool playerDetected);

bool attack();
void loseHealth(int damage);
void move(Coord& delta);
void setPlayerDetected(bool playerDetected);

Coord& getPos();
int getHealth();
int getDamage();
int getRangeOfVisibility();
bool getPlayerDetected();
std::pair<int, int>& getRangeOfX();
std::pair<int, int>& getRangeOfY();

bool wasDetectionOfPlayer(Coord& posPlayer);
};
#endif