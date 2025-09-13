#include "../include/Item.h"

Item::Item(int price) : price(price){}

int Item::getPrice() {
  return price;
}
