#ifndef MAP_H
#define MAP_H
#include <vector>

#include "../util/json/json.h"
#include "../util/json/json-forwards.h"
#include "base_character.h"
#include "fixed_tile.h"
#include "stdint.h"
#include "tile.h"
// 1st layer
#define GROUND 1
#define FLOOR 229
#define WALL_1 189
#define WALL_2 190
#define WALL_3 180
#define WALL_4 191
// 2nd layer
#define BUSH_1 164
#define BUSH_2 172

class Map {
 public:
  // Map(int cols, int rows);
  // Crea un nuevo mapa a partir de un JSON
  Map(Json::Value &map_json);
  ~Map();
  void debug_print();
  /*
    Devuelve true si el personaje colocado en x1,y1
    puede moverse a x2,y2. Si no, devuelve false y se queda
    donde estaba. Si logra moverse, los datos del personaje
    son actualizados.
      */
  bool move_character(int x1, int y1, int x2, int y2);
  // Posiciona un personaje en la fila x, columna y
  void place_character(int x, int y, BaseCharacter *b);

 private:
  int rows;
  int cols;
  // Procesa la primera capa del mapa de tiled en el json
  void load_terrain(Json::Value &map_json);
  std::vector<std::vector<Tile *> > matrix;
};

#endif  // MAP_H