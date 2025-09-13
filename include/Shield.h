//
// Created by Edwin_Jarvis on 13.09.2025.
//

#ifndef UNDERDED_SHIELD_H
#define UNDERDED_SHIELD_H
#include "Item.h"


class Shield : Item {
protected:
  int durability;

public:
  Shield(int price, int durability);

};


#endif //UNDERDED_SHIELD_H