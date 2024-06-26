#ifndef CLIENT_COMMAND_RECEIVER_H
#define CLIENT_COMMAND_RECEIVER_H

#include <string>

#include "../util/json/json-forwards.h"
#include "../util/json/json.h"
#include "argentum_game.h"
#include "command_factory.h"
#include "common_socket.h"
#include "protocol.h"
#include "thread.h"
#include "command_blocker.h"

class ClientCommandReceiver : public Thread {
 public:
  // Recibe los comandos del cliente y los encola para que el juego los procese
  ClientCommandReceiver(Socket &peer_socket, ArgentumGame *game,
                        ThreadSafeQueue<Command *> *commands_queue,
                        unsigned int hero_id);
  ~ClientCommandReceiver() override;
  void run() override;
  bool is_alive();
  void stop();

 private:
  ArgentumGame *game;
  Socket &peer_socket;
  ThreadSafeQueue<Command *> *commands_queue;
  unsigned int hero_id;
  bool alive;
  CommandBlocker command_blocker;
};

#endif  // CLIENT_COMMAND_RECEIVER_H
