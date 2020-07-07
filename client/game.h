#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <vector>

#include "character.h"
#include "item.h"
#include "npc.h"
#include "playable_character.h"
#include "sound_effect.h"
#include "texture.h"
#include "texture_manager.h"
#include "types.h"

#define MAP_SIZE 3200
#define WIDTH_UI 180
#define HEIGHT_UI 135

typedef struct {
  id_texture_t type_item = ID_NULL;
  int x = 0;
  int y = 0;
} dropped_t;

class Game {
 private:
  int id_hero;
  id_texture_t background;
  id_texture_t static_objects;
  // La porción del mapa que queremos renderizar
  SDL_Rect map_piece;
  // La parte de la ventana que es renderizable
  SDL_Rect viewport;
  int screen_width;
  int screen_height;
  std::map<int, Character*> characters;
  std::map<int, dropped_t> items;

 public:
  Game(int, int, int);
  Game(const Game&);
  Game& operator=(const Game&);
  ~Game();
  void render(SDL_Renderer*);
  void update_map(int, int);
  void update_character(int, int, int);
  void update_spellbound(int, id_texture_t, int);
  void change_map(int);
  void load_character(int, entity_t, int, int);
  void load_item(int, item_t, int, int);
  void render_entities(SDL_Renderer*);
  void clean_entity(int i, entity_t);
  void clean_all_characters();
  id_texture_t get_item_texture(item_t) const;
};

#endif