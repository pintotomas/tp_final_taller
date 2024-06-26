#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H
#include <unistd.h>

#include <fstream>
#include <mutex>
#include <vector>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "../util/thread.h"
#include "../util/thread_safe_queue.h"
#include "banker.h"
#include "base_character.h"
#include "command.h"  //<- guarda con esto y dependencias circulares
#include "drop.h"
#include "drops_manager.h"
#include "game_status_notification.h"
#include "hero.h"
#include "heroes_manager.h"
#include "map.h"
#include "merchant.h"
#include "monster.h"
#include "monsters_manager.h"
#include "move_command.h"
#include "priest.h"
#include "projectile.h"
#include "projectiles_manager.h"
#include "serializer.h"
#define PRIEST 33
#define MERCHANT 34
#define BANKER 35

class ArgentumGame : public Thread {
 public:
  // Instancia una nueva sala de Argentum
  // ArgentumGame(const unsigned int room,
  //              ThreadSafeQueue<Command *> *commands_queue,
  //              std::ifstream &map_config, std::ifstream &entities_config);
  ArgentumGame(const unsigned int room,
               ThreadSafeQueue<Command *> *commands_queue, Json::Value &map_cfg,
               std::ifstream &entities_config);
  ~ArgentumGame() override;
  void run() override;
  unsigned int get_room();
  void kill();
  void print_debug_map();
  void hero_dequip_item(int entity_id, int item_id);
  // equipa o usa una pocion
  void hero_use_item(int entity_id, int item_id);
  void move_entity(int entity_id, int x, int y);
  void throw_projectile(int attacker_id);
  void pick_up_drop(unsigned int player_id);
  // Settea a un jugador como muerto para que sea removido durante el update()
  void kill_player(unsigned int player_id);
  // devuelve el id auto-generado
  unsigned int add_new_hero(std::string hero_race, std::string hero_class,
                            std::string hero_name);
  void add_notification_queue(BlockingThreadSafeQueue<Notification *> *queue);
  // remueve colas de notificaciones para no notificar a clientes meurtos
  void clean_notifications_queues();

  friend class Serializer;

 private:
  unsigned int room = 0;
  // A esta cola deberian tener acceso tambien los clientes conectados a esta
  // sala, cuando envian un comando nuevo se encolan y en cada update() del
  // juego se van procesando
  ThreadSafeQueue<Command *> *commands_queue;
  std::mutex mutex;
  std::string map_name;
  Map map;
  bool alive = true;
  // actualiza el mundo segun los comandos recibidos
  // si recibe true, ademas,  aplica los cambios que se deberian aplicar pasado
  // un segundo
  // void update(bool one_second_update);
  void update();
  // segun los ids de la capa 2 del json generado por tiled,
  // coloca a los monstruos iniciales del mapa.
  void place_initial_npcs(Json::Value &map_cfg);
  // void remove_death_entities();
  // entities se usa para serializar el mapa (quitar mas adelante)
  // std::map<unsigned int, Entity *> entities;
  std::map<unsigned int, Entity *> npcs;
  std::map<unsigned int, Hero *> heroes;
  std::map<unsigned int, Monster *> monsters;
  std::map<unsigned int, Projectile *> projectiles;
  std::map<std::tuple<unsigned int, unsigned int>, Drop *> drops;

  std::vector<unsigned char> send_game_status();
  Json::Value entities_cfg;
  unsigned int entities_ids = 0;
  std::vector<BlockingThreadSafeQueue<Notification *> *> queues_notifications;
  std::tuple<unsigned int, unsigned int> get_contiguous_position(
      BaseCharacter *character);
  // agrega heroe en posicion x,y (los ejes estan invertidos)
  unsigned int place_hero(std::string hero_race, std::string hero_class,
                          std::string hero_name, unsigned int x,
                          unsigned int y);
  void tests_proyectiles();
  void tests_drops();
  void place_monster(unsigned int x, unsigned int y);
  ProjectileManager projectile_manager;
  HeroesManager heroes_manager;
  MonstersManager monsters_manager;
  DropsManager drops_manager;
};

#endif  // ARGENTUMGAME_H
