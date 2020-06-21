#include "client_listener.h"

#include <iostream>

#include "client_handler.h"

ClientListener::ClientListener(const char *port, const char *map_cfg_file,
                               const char *entities_cfg_file) {
  Socket server_socket;
  server_socket.bind_and_listen(port);
  this->server_socket = std::move(server_socket);
  const int rooms = 1;
  for (int i = 0; i < rooms; i++) {
    std::ifstream map_file(map_cfg_file);
    std::ifstream entities_file(entities_cfg_file);
    ThreadSafeQueue<Command *> *commands_queue =
        new ThreadSafeQueue<Command *>();

    ArgentumGame *game =
        new ArgentumGame(i, commands_queue, map_file, entities_file);
    game->start();
    games.emplace_back(game);
    queues_commands.emplace_back(commands_queue);
  }
}

ClientListener::~ClientListener() { join(); }

void ClientListener::stop_listening() {
  for (ClientHandler *c : clients) {
    delete c;
  }
  for (ArgentumGame *g : games) {
    g->kill();
    delete g;
  }
  for (ThreadSafeQueue<Command *> *q : queues_commands) {
    delete q;
  }
  server_socket.close();
}
void ClientListener::run() {
  while (true) {
    Socket clientSkt;
    try {
      clientSkt = this->server_socket.accept();
    } catch (std::invalid_argument) {
      break;
    }
    /*
    std::cout << "New client trying to join server!" << std::endl;
    Json::Value starting_info = Protocol::receiveMessage(clientSkt);
    std::cout << "numero hab: " << starting_info["roomNumber"] << std::endl;
    unsigned int room_number = starting_info["roomNumber"].asInt();
    */
    std::cout << "trying to get rno" << std::endl;
    unsigned int room_number =
        static_cast<unsigned int>(Protocol::receive_command(clientSkt) - '0');
    std::cout << "room number received: " << room_number << std::endl;
    BlockingThreadSafeQueue<Notification *> *notifications_queue =
        new BlockingThreadSafeQueue<Notification *>();
    // aca a game pasarle la cola de notificaciones para que la agregue de
    // manera segura (con locks) a el vector de notificaciones, si no puede
    // haber race conditions
    games[room_number]->add_notification_queue(notifications_queue);
    ClientHandler *client =
        new ClientHandler(std::move(clientSkt), games[room_number],
                          queues_commands[room_number], notifications_queue);
    clients.push_back(client);
    // client->start();
    garbage_collector();
  }
}

void ClientListener::garbage_collector() {
  std::list<ClientHandler *>::iterator it = clients.begin();
  while (it != clients.end()) {
    if (!(*it)->is_alive()) {
      std::cout << "Client is dead!" << std::endl;
      delete *it;
      it = clients.erase(it);
    } else {
      it++;
    }
  }
}
