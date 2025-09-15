#ifndef INVENTORY_H
#define INVENTORY_H

class Player; // forward

class Inventory {
public:
  Inventory(int money = 0, int bullets = 0, int aidkits = 0)
      : money_(money), bullets_(bullets), aidkits_(aidkits) {}

  int getMoney() const { return money_; }
  void setMoney(int m) { money_ = m; }
  bool tryBuy(int price);

  int getBulletAmount() const { return bullets_; }
  void setBulletAmount(int v) { bullets_ = v; }
  void addBullets(int v) { bullets_ += v; if (bullets_ < 0) bullets_ = 0; }
  bool spendBullet();

  int getAidKitAmount() const { return aidkits_; }
  void setAidKitAmount(int v) { aidkits_ = v; }
  void addAidKits(int v) { aidkits_ += v; if (aidkits_ < 0) aidkits_ = 0; }
  bool useMedkit(Player& player);

  int  getShieldCharges() const { return shield_charges_; }
  void setShieldCharges(int v) { shield_charges_ = v; if (shield_charges_ < 0) shield_charges_ = 0; }
  void addShield(int v) { shield_charges_ += v; if (shield_charges_ < 0) shield_charges_ = 0; }
  bool useShieldOnce();

private:
  int money_ = 0;
  int bullets_ = 0;
  int aidkits_ = 0;
  int shield_charges_ = 0;
};

#endif
