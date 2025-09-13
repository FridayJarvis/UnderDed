#include "../include/InputHandler.h"
#include "GameManager.h"
#include <iostream>
#include <conio.h>




void InputHandler::initialize() {
  // Стандартные привязки клавиш
  bindKey('W', [](GameManager& gm) { gm.getPlayer().move(0, -1); });
  bindKey('S', [](GameManager& gm) { gm.getPlayer().move(0, 1); });
  bindKey('A', [](GameManager& gm) { gm.getPlayer().move(-1, 0); });
  bindKey('D', [](GameManager& gm) { gm.getPlayer().move(1, 0); });
  bindKey('E', [](GameManager& gm) { gm.interact(); });
  bindKey('I', [](GameManager& gm) { gm.toggleInventory(); });
  bindKey(27, [](GameManager& gm) { gm.pauseGame(); }); // ESC
}

InputHandler::InputHandler() {
  initialize();
}

void InputHandler::handleInput() {
}

void InputHandler::bindKey(int key, Command command) {
}

void InputHandler::clearBindings() {
}

void InputHandler::processInput(GameManager& gameManager) {
  // Очищаем состояния предыдущего кадра
  pressedKeys_.clear();
  pressedMouseButtons_.clear();

  // Проверяем доступность ввода
  if (_kbhit()) { // Windows
    // if (kbhit()) { // Linux alternative
    int key = _getch(); // Windows
    // int key = getchar(); // Linux

    // Преобразуем в верхний регистр
    if (key >= 'a' && key <= 'z') {
      key = toupper(key);
    }

    pressedKeys_.push_back(key);

    // Выполняем привязанную команду
    auto it = keyBindings_.find(key);
    if (it != keyBindings_.end()) {
      it->second(gameManager); // Вызов команды
    }
  }
}

bool InputHandler::isKeyPressed(int keyCode) const {
}
