#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <memory>
#include <vector>

#include "Enemy.h"
#include "InputHandler.h"
#include "Player.h"
#include "Shop.h"


class GameManager {
  std::unique_ptr<Player> player;
  std::unique_ptr<InputHandler> inputPlayer;
  std::unique_ptr<SaveLoadManager> saveLoadManager;

  std::vector<std::unique_ptr<Shop>> shops;

  std::vector<std::string> map;
  std::vector<Enemy> enemies;
};



#endif //GAMEMANAGER_H
