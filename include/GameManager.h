#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <memory>
#include <vector>

#include "Enemy.h"
#include "InputHandler.h"
#include "Player.h"
#include "SaveLoadManager.h"
#include "Shop.h"


class GameManager {
  Player player;
  InputHandler inputHandler;
  SaveLoadManager saveLoadManager;

  std::vector<Shop> shops;

  std::vector<std::string> map;
  std::vector<Enemy> enemies;

  bool initialize();
  void update();
  void render();

  void loadResources();
  void setUpInputHandler();
  void processCollisions();
  void checkWinConditions();

public:
  GameManager(Player& player, InputHandler& inputHandler, SaveLoadManager& saveLoadManager, std::vector<Shop>& shops, std::vector<std::string>& map, std::vector<Enemy>& enemies);

  void run();

  std::vector<std::string>& getMap() ;
  Player& getPlayer();
  std::vector<Enemy> getEnemies();

  void setPlayer(const Player& player);
  void setEnemies(const std::vector<Enemy>& enemies);
};



#endif //GAMEMANAGER_H
