#include "game.h"

Game::Game(int id_player, int scr_width, int scr_height)
    : id_hero(id_player), screen_width(scr_width), screen_height(scr_height) {
  background = ID_MAP_GRASS_BACKGROUND;
  static_objects = ID_MAP_GRASS_OBJECTS;
  map_piece = {0, 0, screen_width, screen_height};
  viewport = {0, 0, screen_width, screen_height};
}

Game::Game(const Game& other_game) {
  id_hero = other_game.id_hero;
  screen_width = other_game.screen_width;
  screen_height = other_game.screen_height;
  background = other_game.background;
  static_objects = other_game.static_objects;
  map_piece = other_game.map_piece;
  viewport = other_game.viewport;

  if (!characters.empty()) characters.clear();

  std::map<int, Character*>::const_iterator it;
  for (it = other_game.characters.begin(); it != other_game.characters.end();
       it++) {
    Npc* npc = dynamic_cast<Npc*>(it->second);
    PlayableCharacter* pc = dynamic_cast<PlayableCharacter*>(it->second);
    if (npc != nullptr)
      characters[it->first] = new Npc(*npc);
    else
      characters[it->first] = new PlayableCharacter(*pc);
  }
}

Game& Game::operator=(const Game& other_game) {
  id_hero = other_game.id_hero;
  screen_width = other_game.screen_width;
  screen_height = other_game.screen_height;
  background = other_game.background;
  static_objects = other_game.static_objects;
  map_piece = other_game.map_piece;
  viewport = other_game.viewport;

  if (!characters.empty()) {
    characters.clear();
  }

  std::map<int, Character*>::const_iterator it;
  for (it = other_game.characters.begin(); it != other_game.characters.end();
       it++) {
    Npc* npc = dynamic_cast<Npc*>(it->second);
    PlayableCharacter* pc = dynamic_cast<PlayableCharacter*>(it->second);
    if (npc != nullptr)
      characters[it->first] = new Npc(*npc);
    else
      characters[it->first] = new PlayableCharacter(*pc);
  }
  return *this;
}

Game::~Game() {
  if (!characters.empty()) characters.clear();
}

void Game::update_character(int id, int new_x, int new_y) {
  // Necesitamos traducir las posiciones de tiles a pixeles
  int x_render_scale = new_x * TILE_SIZE;
  int y_render_scale = new_y * TILE_SIZE;

  // Si se actualiza el heroe la camara lo tiene que seguir
  if (id == id_hero)
    update_map(x_render_scale - characters[id]->get_x(),
               y_render_scale - characters[id]->get_y());

  // Si el personaje se mueve dentro del viewport emite sonido
  if ((map_piece.x < x_render_scale) &&
      (x_render_scale < map_piece.x + screen_width))
    if ((map_piece.y < y_render_scale) &&
        (y_render_scale < map_piece.y + screen_width))
      characters[id]->sound_walk();

  // Actualizamos la posición
  characters[id]->update_position(new_x, new_y);
}

void Game::update_map(int new_x, int new_y) {
  map_piece.x += new_x;
  map_piece.y += new_y;

  if (map_piece.x > MAP_SIZE - screen_width) {
    viewport.w = screen_width - (map_piece.x - (MAP_SIZE - screen_width));
    map_piece.w = screen_width - (map_piece.x - (MAP_SIZE - screen_width));
  } else {
    viewport.w = screen_width;
    map_piece.w = screen_width;
  }
  if (map_piece.y > MAP_SIZE - screen_height) {
    viewport.h = screen_height - (map_piece.y - (MAP_SIZE - screen_height));
    map_piece.h = screen_height - (map_piece.y - (MAP_SIZE - screen_height));
  } else {
    viewport.h = screen_height;
    map_piece.h = screen_height;
  }
  if (map_piece.x < 0) {
    viewport.x = -map_piece.x;
    map_piece.w = screen_width - map_piece.x;
  } else {
    viewport.x = 0;
    map_piece.w = screen_width;
  }
  if (map_piece.y < 0) {
    viewport.y = -map_piece.y;
    map_piece.h = screen_height - map_piece.y;
  } else {
    viewport.y = 0;
    map_piece.h = screen_height;
  }
}

void Game::update_spellbound(int id, id_texture_t spell_type, int lifetime) {
  characters[id]->set_spell(spell_type, lifetime);
}

void Game::render(SDL_Renderer* renderer) {
  // Renderizamos el fondo estático
  texture_manager.get_texture(background)
      .render(renderer, &map_piece, &viewport);

  // Renderizamos las entidades "vivientes"
  render_characters(renderer);

  // Renderizamos los objetos que tapan a las entidades
  texture_manager.get_texture(static_objects)
      .render(renderer, &map_piece, &viewport);
}

void Game::load_character(int id, character_t char_type, int x, int y) {
  if (char_type == HUMAN || char_type == ELF || char_type == GNOME ||
      char_type == DWARF) {
    characters[id] = new PlayableCharacter(char_type, x, y);
    // Si cargamos a hero por primera vez ubicamos el viewport donde debe
    if (id == id_hero)
      update_map(x * TILE_SIZE - screen_width / 2,
                 y * TILE_SIZE - screen_height / 2);
  } else {
    characters[id] = new Npc(char_type, x, y);
  }
}

void Game::render_characters(SDL_Renderer* renderer) {
  std::map<int, Character*>::iterator it;
  for (it = characters.begin(); it != characters.end(); it++) {
    // El personaje DEBE estar dentro del viewport
    if ((map_piece.x <= it->second->get_x()) &&
        (it->second->get_x() <= map_piece.x + screen_width))
      if ((map_piece.y <= it->second->get_y()) &&
          (it->second->get_y() <= map_piece.y + screen_height)) {
        it->second->render(renderer, map_piece.x, map_piece.y);
      }
  }
}

void Game::clean_character(int i) {
  delete characters[i];
  characters.erase(i);
}

void Game::clean_all_characters() {
  std::map<int, Character*>::iterator it;
  for (it = characters.begin(); it != characters.end(); it++) {
    delete characters[it->first];
    characters.erase(it->first);
  }
}