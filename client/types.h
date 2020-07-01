#ifndef TYPES_H
#define TYPES_H

typedef enum {
  ID_NULL = 0,
  ID_HUMAN,
  ID_HUMAN_HEAD,
  ID_ELF,
  ID_ELF_HEAD,
  ID_GNOME,
  ID_GNOME_HEAD,
  ID_DWARF,
  ID_DWARF_HEAD,
  ID_SPIDER,
  ID_SKELETON,
  ID_GOBLIN,
  ID_ZOMBIE,
  ID_PRIEST,
  ID_MERCHANT,
  ID_BANKER,
  ID_MAP_GRASS_BACKGROUND,
  ID_MAP_GRASS_OBJECTS,
  ID_SWORD,
  ID_SWORD_EQUIPPED,
  ID_AXE,
  ID_AXE_EQUIPPED,
  ID_HAMMER,
  ID_HAMMER_EQUIPPED,
  ID_ASH_STICK,
  ID_ASH_STICK_EQUIPPED,
  ID_KNOTTY_STAFF,
  ID_KNOTTY_STAFF_EQUIPPED,
  ID_CRIMPED_STAFF,
  ID_CRIMPED_STAFF_EQUIPPED,
  ID_SIMPLE_BOW,
  ID_SIMPLE_BOW_EQUIPPED,
  ID_COMPOUND_BOW,
  ID_COMPOUND_BOW_EQUIPPED,
  ID_IRON_SHIELD,
  ID_IRON_SHIELD_EQUIPPED,
  ID_TURTLE_SHIELD,
  ID_TURTLE_SHIELD_EQUIPPED,
  ID_MAGIC_HAT,
  ID_MAGIC_HAT_EQUIPPED,
  ID_HOOD,
  ID_HOOD_EQUIPPED,
  ID_IRON_HELMET,
  ID_IRON_HELMET_EQUIPPED,
  ID_LEATHER_ARMOR,
  ID_LEATHER_ARMOR_EQUIPPED,
  ID_LEATHER_ARMOR_XS_EQUIPPED,
  ID_PLATE_ARMOR,
  ID_PLATE_ARMOR_EQUIPPED,
  ID_PLATE_ARMOR_XS_EQUIPPED,
  ID_BLUE_TUNIC,
  ID_BLUE_TUNIC_EQUIPPED,
  ID_MAGIC_ARROW,
  ID_ELECTRIC_SHOCK,
  ID_HEAL,
  ID_EXPLOSION,
  ID_EXPLOSION_1,
  ID_EXPLOSION_2,
  ID_EXPLOSION_3,
  ID_EXPLOSION_4,
  ID_EXPLOSION_5,
  ID_EXPLOSION_6,
  ID_EXPLOSION_7,
  ID_EXPLOSION_8,
  ID_EXPLOSION_9,
  ID_EXPLOSION_10,
  ID_EXPLOSION_11,
  ID_EXPLOSION_12,
  ID_EXPLOSION_13,
  ID_EXPLOSION_14,
  ID_EXPLOSION_15,
  ID_EXPLOSION_16,
  ID_EXPLOSION_17,
  ID_EXPLOSION_18,
  ID_EXPLOSION_19,
  ID_EXPLOSION_20
} id_texture_t;

typedef enum {
  HUMAN = 0,
  ELF,
  GNOME,
  DWARF,
  SPIDER,
  GOBLIN,
  ZOMBIE,
  SKELETON,
  MERCHANT,
  BANKER,
  PRIEST
} character_t;

typedef enum {
  MOVE_DOWN = 0,
  MOVE_UP = 3,
  MOVE_LEFT = 2,
  MOVE_RIGHT = 1
} move_t;

typedef enum { EVENT_NONE = 0, EVENT_QUIT } event_t;

typedef enum { HELMET, ARMOR, WEAPON, SHIELD } item_t;

#endif