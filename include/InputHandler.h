#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <functional>
#include <map>


class GameManager;

class InputHandler {
public:
  using Command = std::function<void(GameManager&)>;

  void initialize();

  InputHandler();

  void handleInput();
  void bindKey(int key, Command command);
  void clearBindings();
  void processInput(GameManager& gameManager);

  bool isKeyPressed(int keyCode);

private:
  std::map<int, Command> keyBindings;

  std::vector<int> pressedKeys;
};


#endif //INPUTHANDLER_H
