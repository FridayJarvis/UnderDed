#include "Inventory.h"
#include "Player.h"
#include <algorithm>

bool Inventory::tryBuy(int price) {
  if (price < 0) return false;
  if (money_ < price) return false;
  money_ -= price;
  return true;
}

bool Inventory::spendBullet() {
  if (bullets_ <= 0) return false;
  --bullets_;
  return true;
}

bool Inventory::useMedkit(Player& player) {
  if (aidkits_ <= 0) return false;
  --aidkits_;
  player.setHealth(std::min(10, player.getHealth() + 5));
  return true;
}

bool Inventory::useShieldOnce() {
  if (shield_charges_ <= 0) return false;
  --shield_charges_;
  return true;
}
