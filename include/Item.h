//
// Created by Edwin_Jarvis on 13.09.2025.
//

#ifndef UNDERDED_ITEM_H
#define UNDERDED_ITEM_H


class Item {
protected:
  int price;

public:
  Item(int price);

  int getPrice();

  virtual ~Item();
};


#endif //UNDERDED_ITEM_H