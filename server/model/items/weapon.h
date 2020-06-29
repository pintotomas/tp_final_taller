#ifndef WEAPON_H
#define WEAPON_H
#include "item.h"
class Item;
class Weapon : public Item {
 public:
  Weapon(int id, unsigned int min_damage, unsigned int max_damage,
         unsigned int range);
  virtual ~Weapon();
  Weapon(const Weapon &) = delete;
  unsigned int min_damage, max_damage, range;
};
#endif  // WEAPON_H