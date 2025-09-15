#include "InputHandler.h"
#include "GameManager.h"
#include <cctype>
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#endif

InputHandler::InputHandler() {
  clearBindings();
  // Движение
  bindKey('W', [](GameManager& gm){ gm.movePlayer(0,-1); });
  bindKey('S', [](GameManager& gm){ gm.movePlayer(0, 1); });
  bindKey('A', [](GameManager& gm){ gm.movePlayer(-1,0); });
  bindKey('D', [](GameManager& gm){ gm.movePlayer(1, 0); });
  // Бой/щит/инвентарь/магазин
  bindKey(' ', [](GameManager& gm){ gm.playerAttack(); });
  bindKey('Q', [](GameManager& gm){ gm.useShield(); });
  bindKey('I', [](GameManager& gm){ gm.toggleInventory(); });
  bindKey('F', [](GameManager& gm){ gm.openShopIfAny(); });
  // Оружие
  bindKey('1', [](GameManager& gm){ gm.selectWeapon(1); });
  bindKey('2', [](GameManager& gm){ gm.selectWeapon(2); });
  bindKey('3', [](GameManager& gm){ gm.selectWeapon(3); });
  // Save/Load
  bindKey('Z', [](GameManager& gm){ gm.saveGame(); });
  bindKey('X', [](GameManager& gm){ gm.loadGame(); });
}

void InputHandler::handleInput() {}

void InputHandler::bindKey(int key, Command cmd) {
  keyBindings[normalize(key)] = std::move(cmd);
}

void InputHandler::clearBindings() {
  keyBindings.clear();
}

void InputHandler::processInput(GameManager& gm) {
  const int k = readKey();
  if (k < 0) return;
  auto it = keyBindings.find(normalize(k));
  if (it != keyBindings.end()) it->second(gm);
}

bool InputHandler::isKeyPressed(int) const { return false; }

int InputHandler::normalize(int k) {
  if (k >= 'a' && k <= 'z') return std::toupper(k);
  return k;
}

int InputHandler::readKey() {
#ifdef _WIN32
  if (_kbhit()) {
    int ch = _getch();
    return ch;
  }
  return -1;
#else
  int ch = std::cin.get();
  if (ch == EOF) return -1;
  return ch;
#endif
}
