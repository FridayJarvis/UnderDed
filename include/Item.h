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