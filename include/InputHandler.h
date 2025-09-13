#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <functional>
#include <map>

#include "GameManager.h"

class InputHandler {
public:
  using Command = std::function<void(GameManager&)>;

  void initialize();

  InputHandler();

  void handleInput();
  void bindKey(int key, Command command);
  void clearBindings();
  void processInput(GameManager& gameManager);

  bool isKeyPressed(int keyCode) const;

private:
  std::map<int, Command> key_bindings;

  std::vector<int> pressedKeys;
};


#endif //INPUTHANDLER_H
