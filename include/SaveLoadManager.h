#ifndef SAVELOADMANAGER_H
#define SAVELOADMANAGER_H

#include <string>
#include <vector>
#include "Player.h"
#include "Enemy.h"

class SaveLoadManager {
public:
  bool save(const std::string& path,
            Player& player,
            std::vector<std::string>& map,
            std::vector<Enemy>& enemies,
            std::string& map_path);

  bool load(const std::string& path,
            Player& player,
            std::vector<std::string>& map,
            std::vector<Enemy>& enemies,
            std::string& map_path);
};

#endif
