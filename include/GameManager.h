#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include "Coord.h"
#include "Player.h"
#include "Enemy.h"
#include "Shop.h"
#include "SaveLoadManager.h"

class InputHandler;

class GameManager {
 public:
  GameManager(Player& player,
              InputHandler& input_handler,
              SaveLoadManager& save_load,
              std::vector<Shop>& shops,
              std::vector<std::string>& map,
              std::vector<Enemy>& enemies);

  void run();

  std::vector<std::string>& getMap();
  Player& getPlayer();
  std::vector<Enemy>& getEnemies();

  void movePlayer(int dx, int dy);
  void playerAttack();
  void useShield();
  void toggleInventory();
  void openShopIfAny();
  void selectWeapon(int slot);
  void saveGame();
  void loadGame();

 private:
  bool initialize();
  void update();
  void render();
  void processCollisions();
  void checkWinConditions();

  bool loadMapFromFile(const std::string& path);
  void sanitizeAndNormalizeRow(std::string& row);
  bool inBounds(int x, int y) const;
  bool isWall(int x, int y) const;
  bool isShopCell(int x, int y) const;
  bool isGoalCell(int x, int y) const;

  void attackFists();
  void attackSpear();
  void attackPistol();
  int  findEnemyAt(int x, int y) const;
  void aiStepEnemies();

  void buildFrame(std::string& out) const;
  void clearConsole() const;  // ANSI

  Player& player_;
  InputHandler& input_handler_;
  SaveLoadManager& save_load_manager_;

  std::vector<Shop>& shops_;
  std::vector<std::string>& map_;
  std::vector<Enemy>& enemies_;

  bool running_ = true;
  std::string map_path_ = "../assets/UnderDedMap.txt";

  Coord spawn_{0, 0};
  Coord goal_{-1, -1};

  int last_dx_ = 0;
  int last_dy_ = -1; //
};

#endif
