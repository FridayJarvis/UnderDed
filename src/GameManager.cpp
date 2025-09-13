#include "GameManager.h"
#include "Enemy.h"
#include "InputHandler.h"

bool GameManager::initialize() {
  return true;
}

void GameManager::update() {
}

void GameManager::render() {
}

void GameManager::loadResources() {
}

void GameManager::setUpInputHandler() {
}

void GameManager::processCollisions() {
}

void GameManager::checkWinConditions() {
}

GameManager::GameManager(Player player, InputHandler& inputHandler, SaveLoadManager& saveLoadManager,
  std::vector<Shop>& shops, std::vector<std::string>& map, std::vector<Enemy>& enemies)
    : player(std::move(player)), inputHandler(inputHandler), saveLoadManager(saveLoadManager),
      shops(shops), map(map), enemies(enemies) {
}

void GameManager::run() {
}

std::vector<std::string>& GameManager::getMap() {
  static std::vector<std::string> vec {"41232"};
  return vec;
}


Player & GameManager::getPlayer() {
  return player;
}

std::vector<Enemy>& getEnemies() {
  static std::vector<Enemy> stubEnemies = {
    Enemy({2, 3}, {50, 100}, {20, 35}, 1, 2, 1, 3, false)
};
  return stubEnemies;
}

void GameManager::setPlayer(Player& player) {
}

void GameManager::setEnemies(std::vector<Enemy>& enemies) {
}
