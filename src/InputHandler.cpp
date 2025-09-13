#include <conio.h>
#include "InputHandler.h"

#include <cctype>

#include "GameManager.h"

void InputHandler::initialize() {
  // Стандартные привязки клавиш
  bindKey('W', [](GameManager& gm) { gm.getPlayer().move({0, -1}); });
  bindKey('S', [](GameManager& gm) { gm.getPlayer().move({0, 1}); });
  bindKey('A', [](GameManager& gm) { gm.getPlayer().move({-1, 0}); });
  bindKey('D', [](GameManager& gm) { gm.getPlayer().move({1, 0}); });
  // bindKey('Q', [](GameManager& gm) { gm.interact(); });
  // bindKey('I', [](GameManager& gm) { gm.toggleInventory(); });
  // bindKey(27, [](GameManager& gm) { gm.pauseGame(); }); // ESC
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
  pressedKeys.clear();
  // Проверяем доступность ввода
  if (_kbhit()) { // Windows
    // if (kbhit()) { // Linux alternative
    int key = _getch(); // Windows
    // int key = getchar(); // Linux

    // Преобразуем в верхний регистр
    if (key >= 'a' && key <= 'z') {
      key = toupper(key);
    }

    pressedKeys.push_back(key);

    // Выполняем привязанную команду
    auto it = keyBindings.find(key);
    if (it != keyBindings.end()) {
      it->second(gameManager); // Вызов команды
    }
  }
}

bool InputHandler::isKeyPressed(int keyCode) {
  return true;
}
