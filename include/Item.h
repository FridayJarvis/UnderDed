#ifndef UNDERDED_ITEM_H
#define UNDERDED_ITEM_H


class Item {
protected:
  int price;

public:
  Item(int price);
  virtual ~Item();

  virtual int getPrice();

};


#endif //UNDERDED_ITEM_H