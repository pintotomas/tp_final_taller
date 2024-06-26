#include "client_notification_sender.h"

#include <iostream>
#include <sstream>
#include <vector>

ClientNotificationSender::ClientNotificationSender(
    Socket& peer_socket, ArgentumGame* game,
    BlockingThreadSafeQueue<Notification*>* notifications_queue)
    : game(game),
      peer_socket(peer_socket),
      notifications_queue(notifications_queue),
      alive(true) {}

ClientNotificationSender::~ClientNotificationSender() {
  join();
  notifications_queue->close();
  
}

void ClientNotificationSender::stop() { this->alive = false; }

void ClientNotificationSender::run() {
  std::cout << "receiver, game room :" << game->get_room() << std::endl;

  while (alive) {

    //bloquea mientras no haya notificaciones
    Notification *n = notifications_queue->pop();
    Protocol::send_notification(this->peer_socket ,n);
    //ver cuando settear alive = false para que se cierre la cola de
    //notificaciones
    delete n;
  }
  std::cout << "stopping notification sender" << std::endl;

}

bool ClientNotificationSender::is_alive() { return this->alive; }
