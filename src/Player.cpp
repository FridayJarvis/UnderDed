#include "../include/Player.h"

#include "GameManager.h"

Player::Player(Coord& position, Inventory& inventory, std::unique_ptr<Weapon> currentWeapon, int health, int speed)
  : position(position), inventory(inventory), currentWeapon(std::move(currentWeapon)) {
  this->health = health;
  this->speed = speed;
}

bool Player::attack(Weapon &weapon) {
  weapon.attack([](GameManager& gm) {
    return gm.getEnemies();
  });
  return true;
}

bool Player::useShield(Shield &shield) {
  return true;
}

void Player::move(Coord &delta) {
}

void Player::loseHealth(int damage) {
}

void Player::changeWeapon(std::unique_ptr<Weapon> weapon) {
  currentWeapon = std::move(weapon);
}

bool Player::addItem(Item &item) {
  return true;
}

bool Player::removeItem(Item &item) {
  return true;
}

int Player::getHealth() {
  return health;
}

Coord& Player::getPosition() {
  return position;
}

int Player::getSpeed() {
  return speed;
}

Inventory& Player::getInventory() {
  return inventory;
}

std::unique_ptr<Weapon> Player::getCurrentWeapon() {
  return std::move(currentWeapon);
}

void Player::setHealth(int health) {
  this->health = health;
}

void Player::setPosition(Coord& position) {
  this->position = position;
}

void Player::setPosition(int x, int y) {
  this->position.x = x;
  this->position.y = y;
}

void Player::setSpeed(int speed) {
  this->speed = speed;
}

void Player::setBulletAmount(int bulletAmount) {
  this->inventory.setBulletAmount(bulletAmount);
}

void Player::setAidKitAmount(int aidKitAmount) {
  this->inventory.setAidKitAmount(aidKitAmount);
}

void Player::setItem(Item& item) {
  this->inventory.setItem(item);
}

void Player::setCurrentWeapon(Weapon& currentWeapon) {
}


