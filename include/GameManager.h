#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <memory>
#include <vector>


class GameManager {
  std::unique_ptr<Player> player;
  std::unique_ptr<InputPlayer> inputPlayer;
  std::unique_ptr<SaveLoadManager> saveLoadManager;

  std::vector<std::unique_ptr<Shop>> shops;

  std::vector<std::string> map;
  std::vector<Enemy> enemies;
};



#endif //GAMEMANAGER_H
