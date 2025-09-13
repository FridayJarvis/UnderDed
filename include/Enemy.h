//
// Created by Edwin_Jarvis on 13.09.2025.
//

#ifndef UNDERDED_ENEMY_H
#define UNDERDED_ENEMY_H
#include <utility>


class Enemy {
  Coord position;

  int damage;
  int health;
  int speed;
  int rangeOfVisibility;

  bool playerDetected;

  std::pair<int, int> rangeOfX;
  std::pair<int, int> rangeOfY;
};


#endif //UNDERDED_ENEMY_H