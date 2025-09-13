#include "../include/GameManager.h"

bool GameManager::initialize() {
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

GameManager::GameManager(Player& player, InputHandler& inputHandler, SaveLoadManager& saveLoadManager,
  std::vector<Shop>& shops, std::vector<std::string>& map, std::vector<Enemy>& enemies) {
  this->player = player;
}

void GameManager::run() {
}

std::vector<std::string> & GameManager::getMap() {
}


Player & GameManager::getPlayer() {
}

std::vector<Enemy> GameManager::getEnemies() {
}

void GameManager::setPlayer(const Player& player) {
}

void GameManager::setEnemies(const std::vector<Enemy>& enemies) {
}
