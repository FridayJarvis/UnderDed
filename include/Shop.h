#ifndef SHOP_H
#define SHOP_H
#include "Coord.h"
#include "Player.h"

class Shop {
  Coord pos;

public:
  Shop(Coord& pos);

  bool Buy(Player& player);
  bool Sell(Player& player);
};



#endif
