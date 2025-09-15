#include <iostream>
#include <vector>
#include <string>

#include "GameManager.h"
#include "InputHandler.h"
#include "SaveLoadManager.h"

int main() {
  std::vector<std::string> map;
  std::vector<Enemy> enemies;
  std::vector<Shop> shops;

  Player player;
  InputHandler input;
  SaveLoadManager save;

  GameManager game(player, input, save, shops, map, enemies);
  game.run();
  return 0;
}
