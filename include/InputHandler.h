#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <functional>
#include <map>

class GameManager;

class InputHandler {
public:
  using Command = std::function<void(GameManager&)>;

  InputHandler();

  void handleInput();
  void bindKey(int key, Command cmd);
  void clearBindings();
  void processInput(GameManager& gm);

  bool isKeyPressed(int keyCode) const;

private:
  int readKey();
  static int normalize(int k);

private:
  std::map<int, Command> keyBindings;
};

#endif