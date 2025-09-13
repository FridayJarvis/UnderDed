#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>
#include "Item.h"

class Inventory {
  int money;
  int bulletAmount;
  int aidKitAmount;

  std::vector<Item> items;

public:
  Inventory(int money, int bulletAmount, int aidKitAmount, std::vector<Item>& items);

  void add(Item& item);
  void clear(Item& item);

  int getBulletAmount();
  int getAidKitAmount();
  int getMoney();

  void setBulletAmount(int bulletAmount);
  void setAidKitAmount(int aidKitAmount);
  void setMoney(int money);
  void setItem(Item& item);

};



#endif //INVENTORY_H
