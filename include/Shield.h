#ifndef UNDERDED_SHIELD_H
#define UNDERDED_SHIELD_H
#include "Item.h"


class Shield : Item {
protected:
  int durability;

public:
  Shield(int price, int durability);

};


#endif