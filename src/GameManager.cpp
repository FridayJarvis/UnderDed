#include "GameManager.h"
#include "InputHandler.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace {
constexpr char kPlayerGlyph = '@';
constexpr char kEnemyGlyph  = 'E';

constexpr const char* kAnsiClear = "\x1b[2J\x1b[H";

int sgn(int v) { return (v > 0) - (v < 0); }
}

GameManager::GameManager(Player& player,
                         InputHandler& input_handler,
                         SaveLoadManager& save_load,
                         std::vector<Shop>& shops,
                         std::vector<std::string>& map,
                         std::vector<Enemy>& enemies)
    : player_(player),
      input_handler_(input_handler),
      save_load_manager_(save_load),
      shops_(shops),
      map_(map),
      enemies_(enemies) {}

bool GameManager::initialize() {

  if (map_.empty()) {
    if (!loadMapFromFile(map_path_)) {
      std::cerr << "Failed to load map: " << map_path_ << "\n";
      return false;
    }
  }


  bool has_goal = false;
  for (int y = 0; y < static_cast<int>(map_.size()); ++y) {
    for (int x = 0; x < static_cast<int>(map_[y].size()); ++x) {
      const char c = map_[y][x];
      if (c == 'S') spawn_ = {x, y};
      if (c == '$') shops_.emplace_back(*(new Coord{ x, y }));
      if (c == 'X') { goal_ = {x, y}; has_goal = true; }
    }
  }
  if (!has_goal) {

    int gy = static_cast<int>(map_.size()) - 1;
    int gx = map_.empty() ? 0 : static_cast<int>(map_[gy].size()) - 1;
    goal_ = {gx, gy};
  }

  player_.setPosition(spawn_);
  player_.setHealth(10);
  player_.getInventory().setMoney(20);
  player_.getInventory().setBulletAmount(0);
  player_.getInventory().setAidKitAmount(0);
  player_.getInventory().setShieldCharges(0);
  return true;
}

void GameManager::run() {
  if (!initialize()) return;

  render();
  while (running_) {
    input_handler_.processInput(*this);
    update();
    processCollisions();
    checkWinConditions();
    render();
  }
}

std::vector<std::string>& GameManager::getMap() { return map_; }
Player& GameManager::getPlayer() { return player_; }
std::vector<Enemy>& GameManager::getEnemies() { return enemies_; }


void GameManager::movePlayer(int dx, int dy) {
  if (dx != 0 && dy != 0) return;
  Coord p = player_.getPosition();
  const int nx = p.x + dx;
  const int ny = p.y + dy;
  if (inBounds(nx, ny) && !isWall(nx, ny)) {
    player_.setPosition(nx, ny);
    last_dx_ = sgn(dx);
    last_dy_ = sgn(dy);
    if (last_dx_ == 0 && last_dy_ == 0) { last_dy_ = -1; }
  }
}

void GameManager::playerAttack() {
  const int slot = player_.getCurrentWeaponSlot();
  if (slot == 1)      attackFists();
  else if (slot == 2) attackSpear();
  else if (slot == 3) attackPistol();
}

void GameManager::useShield() {
  if (player_.getInventory().useShieldOnce()) {
    std::cout << "[Shield] absorbed next hit.\n";
  } else {
    std::cout << "[Shield] no charges.\n";
  }
}

void GameManager::toggleInventory() {
  auto& inv = player_.getInventory();
  std::cout << "\n=== INVENTORY ===\n";
  std::cout << "HP: " << player_.getHealth() << "/10\n";
  std::cout << "Coins: " << inv.getMoney()
            << " | Bullets: " << inv.getBulletAmount()
            << " | Medkits: " << inv.getAidKitAmount()
            << " | Shield: " << inv.getShieldCharges()
            << " | Weapon: " << player_.getCurrentWeaponSlot() << "\n";
  std::cout << "Use medkit? (Y/N): ";
  char c; std::cin >> c;
  if (c == 'Y' || c == 'y') {
    if (inv.useMedkit(player_)) std::cout << "Healed.\n";
    else std::cout << "No medkits.\n";
  }
}

void GameManager::openShopIfAny() {
  const auto p = player_.getPosition();
  if (!isShopCell(p.x, p.y)) {
    std::cout << "No shop here.\n";
    return;
  }

  bool done = false;
  while (!done) {
    auto& inv = player_.getInventory();
    std::cout << "\n==== SHOP ====\n";
    std::cout << "Coins: " << inv.getMoney()
              << " | Bullets: " << inv.getBulletAmount()
              << " | Medkits: " << inv.getAidKitAmount()
              << " | Shield: " << inv.getShieldCharges()
              << " | WeaponSlot: " << player_.getCurrentWeaponSlot() << "\n";
    std::cout << "1) +5 bullets (5$)\n";
    std::cout << "2) +1 medkit  (8$)\n";
    std::cout << "3) +1 shield  (6$)\n";
    std::cout << "4) buy SPEAR  (20$)\n";
    std::cout << "5) buy PISTOL (30$)\n";
    std::cout << "Q) quit\n> ";
    char c; std::cin >> c;
    switch (c) {
      case '1': if (inv.tryBuy(5)) { inv.addBullets(5);  std::cout << "Ammo +5\n"; } else std::cout << "Not enough.\n"; break;
      case '2': if (inv.tryBuy(8)) { inv.addAidKits(1); std::cout << "Medkit +1\n"; } else std::cout << "Not enough.\n"; break;
      case '3': if (inv.tryBuy(6)) { inv.addShield(1);  std::cout << "Shield +1\n"; } else std::cout << "Not enough.\n"; break;
      case '4': if (inv.tryBuy(20)) { player_.unlockWeaponSlot(2); std::cout << "Spear unlocked.\n"; } else std::cout << "Not enough.\n"; break;
      case '5': if (inv.tryBuy(30)) { player_.unlockWeaponSlot(3); std::cout << "Pistol unlocked.\n"; } else std::cout << "Not enough.\n"; break;
      case 'q': case 'Q': done = true; break;
      default: break;
    }
  }
}

void GameManager::selectWeapon(int slot) {
  if (slot < 1 || slot > 3) return;
  player_.setCurrentWeaponSlot(slot);
}

void GameManager::saveGame() {
  save_load_manager_.save("save.json", player_, map_, enemies_, map_path_);
  std::cout << "[Saved] save.json\n";
}
void GameManager::loadGame() {
  if (save_load_manager_.load("save.json", player_, map_, enemies_, map_path_)) {

    shops_.clear();
    bool has_goal = false;
    for (int y = 0; y < static_cast<int>(map_.size()); ++y) {
      for (int x = 0; x < static_cast<int>(map_[y].size()); ++x) {
        const char c = map_[y][x];
        if (c == 'S') spawn_ = {x, y};
        if (c == '$') shops_.emplace_back(*(new Coord{ x, y }));
        if (c == 'X') { goal_ = {x, y}; has_goal = true; }
      }
    }
    if (!has_goal) {
      int gy = static_cast<int>(map_.size()) - 1;
      int gx = map_.empty() ? 0 : static_cast<int>(map_[gy].size()) - 1;
      goal_ = {gx, gy};
    }
    std::cout << "[Loaded] save.json\n";
  } else {
    std::cout << "[Load failed]\n";
  }
}


void GameManager::update() {
  aiStepEnemies();
}

void GameManager::processCollisions() {

  const auto p = player_.getPosition();
  for (auto& e : enemies_) {
    const int d = std::abs(e.getPos().x - p.x) + std::abs(e.getPos().y - p.y);
    if (d == 1) {
      if (!player_.getInventory().useShieldOnce()) {
        player_.loseHealth(e.getDamage());
      }
    }
  }

  enemies_.erase(std::remove_if(enemies_.begin(), enemies_.end(),
                  [](const Enemy& en){ return en.getHealth() <= 0; }),
                  enemies_.end());
}

void GameManager::checkWinConditions() {
  const auto p = player_.getPosition();
  if (isGoalCell(p.x, p.y)) {
    std::cout << "\n*** YOU WIN! ***\n";
    running_ = false;
  }
  if (player_.getHealth() <= 0) {
    std::cout << "\n*** YOU DIED. ***\n";
    running_ = false;
  }
}

void GameManager::render() {
  std::string frame;
  buildFrame(frame);
  clearConsole();
  std::cout << frame;
}


bool GameManager::loadMapFromFile(const std::string& path) {
  map_.clear();
  std::ifstream in(path, std::ios::binary);
  if (!in.is_open()) return false;
  std::string line;
  int maxw = 0;
  while (std::getline(in, line)) {
    if (!line.empty() && line.back() == '\r') line.pop_back();
    sanitizeAndNormalizeRow(line);
    map_.push_back(line);
    maxw = std::max(maxw, (int)line.size());
  }
  in.close();

  for (auto& r : map_) if ((int)r.size() < maxw) r.append(maxw - (int)r.size(), '.');
  map_path_ = path;
  return !map_.empty();
}

void GameManager::sanitizeAndNormalizeRow(std::string& row) {

  static const std::string kBlock = "\xE2\x96\x88";
  size_t pos = 0;
  while ((pos = row.find(kBlock, pos)) != std::string::npos) {
    row.replace(pos, kBlock.size(), "#");
    pos += 1;
  }
  std::replace(row.begin(), row.end(), '\t', ' ');
}

bool GameManager::inBounds(int x, int y) const {
  return y >= 0 && y < (int)map_.size() && x >= 0 && x < (int)map_[y].size();
}
bool GameManager::isWall(int x, int y) const {
  if (!inBounds(x, y)) return true;
  char c = map_[y][x];
  return !(c == '.' || c == 'S' || c == '$' || c == 'X' || c == ' ');
}
bool GameManager::isShopCell(int x, int y) const {
  return inBounds(x, y) && map_[y][x] == '$';
}
bool GameManager::isGoalCell(int x, int y) const {
  if (!inBounds(x, y)) return false;
  if (map_[y][x] == 'X') return true;
  return (x == goal_.x && y == goal_.y);
}

int GameManager::findEnemyAt(int x, int y) const {
  for (int i = 0; i < (int)enemies_.size(); ++i) {
    if (enemies_[i].getPos().x == x && enemies_[i].getPos().y == y) return i;
  }
  return -1;
}

void GameManager::attackFists() {
  const auto p = player_.getPosition();
  const int dx[4] = {1, -1, 0, 0};
  const int dy[4] = {0, 0, 1, -1};
  bool hit = false;
  for (int i = 0; i < 4; ++i) {
    int tx = p.x + dx[i], ty = p.y + dy[i];
    int idx = findEnemyAt(tx, ty);
    if (idx >= 0) { enemies_[idx].loseHealth(1); hit = true; }
  }
  std::cout << "[Fists] " << (hit ? "hit.\n" : "miss.\n");
}

void GameManager::attackSpear() {
  if (last_dx_ == 0 && last_dy_ == 0) last_dy_ = -1;
  const auto p = player_.getPosition();
  bool hit = false;
  for (int s = 1; s <= 3; ++s) {
    int tx = p.x + last_dx_ * s, ty = p.y + last_dy_ * s;
    if (!inBounds(tx, ty) || isWall(tx, ty)) break;
    int idx = findEnemyAt(tx, ty);
    if (idx >= 0) { enemies_[idx].loseHealth(1); hit = true; }
  }
  std::cout << "[Spear] " << (hit ? "hit.\n" : "miss.\n");
}

void GameManager::attackPistol() {
  auto& inv = player_.getInventory();
  if (!inv.spendBullet()) {
    std::cout << "[Pistol] no bullets.\n";
    return;
  }
  if (last_dx_ == 0 && last_dy_ == 0) last_dx_ = 1;
  const auto p = player_.getPosition();
  bool hit = false;
  int tx = p.x, ty = p.y;
  while (true) {
    tx += last_dx_; ty += last_dy_;
    if (!inBounds(tx, ty) || isWall(tx, ty)) break;
    int idx = findEnemyAt(tx, ty);
    if (idx >= 0) { enemies_[idx].loseHealth(1); hit = true; }
  }
  std::cout << "[Pistol] " << (hit ? "hit.\n" : "miss.\n");
}

void GameManager::aiStepEnemies() {
  const auto pp = player_.getPosition();
  for (auto& e : enemies_) {
    int dx = (pp.x > e.getPos().x) ? 1 : (pp.x < e.getPos().x ? -1 : 0);
    int dy = (pp.y > e.getPos().y) ? 1 : (pp.y < e.getPos().y ? -1 : 0);
    if (std::abs(pp.x - e.getPos().x) >= std::abs(pp.y - e.getPos().y)) {
      int nx = e.getPos().x + dx, ny = e.getPos().y;
      if (inBounds(nx, ny) && !isWall(nx, ny)) { e.setPosition(nx, ny); continue; }
      nx = e.getPos().x; ny = e.getPos().y + dy;
      if (inBounds(nx, ny) && !isWall(nx, ny)) { e.setPosition(nx, ny); continue; }
    } else {
      int nx = e.getPos().x, ny = e.getPos().y + dy;
      if (inBounds(nx, ny) && !isWall(nx, ny)) { e.setPosition(nx, ny); continue; }
      nx = e.getPos().x + dx; ny = e.getPos().y;
      if (inBounds(nx, ny) && !isWall(nx, ny)) { e.setPosition(nx, ny); continue; }
    }
  }
}

void GameManager::buildFrame(std::string& out) const {
  out.clear();
  for (int y = 0; y < (int)map_.size(); ++y) {
    std::string row = map_[y];
    for (auto& e : enemies_) {
      if (e.getPos().y == y && e.getPos().x >= 0 && e.getPos().x < (int)row.size()) {
        row[e.getPos().x] = kEnemyGlyph;
      }
    }
    auto p = player_.getPosition();
    if (p.y == y && p.x >= 0 && p.x < (int)row.size()) row[p.x] = kPlayerGlyph;

    out += row;
    out += '\n';
  }
  auto& inv = player_.getInventory();
  out += "HP " + std::to_string(player_.getHealth())
       + " | $ " + std::to_string(inv.getMoney())
       + " | Bullets " + std::to_string(inv.getBulletAmount())
       + " | Medkits " + std::to_string(inv.getAidKitAmount())
       + " | Shield " + std::to_string(inv.getShieldCharges())
       + " | Weapon " + std::to_string(player_.getCurrentWeaponSlot())
       + " | Goal(" + std::to_string(goal_.x) + "," + std::to_string(goal_.y) + ")\n";
  out += "Controls: WASD move | SPACE attack | Q shield | F shop | I inventory | 1/2/3 weapons | Z save | X load\n";
}

void GameManager::clearConsole() const {
  std::cout << kAnsiClear;
}
