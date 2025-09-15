#include "Player.h"

void Player::setCurrentWeaponSlot(int slot) {
  if (slot >= 1 && slot <= 3 && owned[slot]) currentWeaponSlot = slot;
}
void Player::unlockWeaponSlot(int slot) {
  if (slot >= 1 && slot <= 3) owned[slot] = true;
}
