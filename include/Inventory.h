#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>


class Inventory {
  int money;
  int bulletAmount;
  int aidKitAmount;

  std::vector<Item> items;
};



#endif //INVENTORY_H
