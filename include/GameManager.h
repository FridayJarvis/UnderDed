#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
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
  GameManager(Player player, InputHandler& inputHandler,
              SaveLoadManager& saveLoadManager, std::vector<Shop>& shops,
              std::vector<std::string>& map, std::vector<Enemy>& enemies);

  void run();

  std::vector<std::string>& getMap() ;
  Player& getPlayer();
  std::vector<Enemy>& getEnemies();

  void setPlayer(Player& player);
  void setEnemies(std::vector<Enemy>& enemies);
};



#endif
