#include "../include/Enemy.h"

#include <cmath>

Enemy::Enemy(Coord& pos, std::pair<int, int>& rangeOfX,std::pair<int, int> &rangeOfY,
             int damage, int health, int speed, int rangeOfVisibility, bool playerDetected)
  : pos(pos), rangeOfX(rangeOfX), rangeOfY(rangeOfY) {
  this->damage = damage;
  this->health = health;
  this->speed = speed;
  this->rangeOfVisibility = rangeOfVisibility;
  this->playerDetected = playerDetected;
}

bool Enemy::attack() {
  return true;
}

void Enemy::loseHealth(int damage) {
  this->health -= damage;
}

void Enemy::move(Coord& delta) {
  pos.x += delta.x;
  pos.y += delta.y;
}

void Enemy::setPlayerDetected(bool playerDetected) {
  this->playerDetected = playerDetected;
}

Coord& Enemy::getPos() {
  return pos;
}

int Enemy::getHealth() {
  return health;
}

int Enemy::getDamage() {
  return damage;
}

int Enemy::getRangeOfVisibility() {
  return rangeOfVisibility;
}

bool Enemy::getPlayerDetected() {
  return playerDetected;
}

std::pair<int, int>& Enemy::getRangeOfX() {
  return rangeOfX;
}

std::pair<int, int>& Enemy::getRangeOfY() {
  return rangeOfY;
}

bool Enemy::wasDetectionOfPlayer(Coord& posPlayer) {
  if (std::abs(posPlayer.x - pos.x) <= rangeOfVisibility
    && std::abs(posPlayer.y - pos.y) <= rangeOfVisibility) return true;

  return false;
}