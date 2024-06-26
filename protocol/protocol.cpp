#include "protocol.h"

#include <string.h>

#include <iostream>
#include <memory>
#include <vector>

#include "../server/notifications/notification.h"
#include "attack_command_dto.h"
#include "login_command_dto.h"
#include "move_command_dto.h"
#include "pick_up_command_dto.h"
#include "quit_command_dto.h"
#include "use_item_command_dto.h"
#define ID_LENGTH 1

/********************** COMANDOS ***********************************/

LoginCommandDTO* receive_login(const Socket& socket) {
  uint8_t room_number;
  socket.recv(&room_number, 1);
  std::cout << "room number: " << (int)room_number << std::endl;
  return new LoginCommandDTO(room_number);
}

MoveCommandDTO* receive_move(const Socket& socket) {
  uint8_t movement_type;
  socket.recv(&movement_type, 1);
  return new MoveCommandDTO(movement_t(movement_type));
}

UseItemCommandDTO* receive_use_item(const Socket& socket) {
  uint8_t item;
  socket.recv(&item, 1);
  uint8_t item_slot;
  socket.recv(&item_slot, 1);
  uint8_t is_equipped;
  socket.recv(&is_equipped, 1);
  return new UseItemCommandDTO(item, item_slot, is_equipped);
}

CommandDTO* Protocol::receive_command(const Socket& socket) {
  uint8_t command_id;
  int bytes_rcv = socket.recv(&command_id, ID_LENGTH);
  if (bytes_rcv <= 0) return nullptr;  // cerro conexion
  // std::cout << "Command id recibido: " << (int)command_id << std::endl;
  switch (command_id) {
    case LOGIN_COMMAND:
      return receive_login(socket);
    case QUIT_COMMAND:
      return new QuitCommandDTO();
    case MOVE_COMMAND:
      return receive_move(socket);
    case ATTACK_COMMAND:
      return new AttackCommandDTO();
    case PICK_UP_ITEM_COMMAND:
      return new PickUpCommandDTO();
    case USE_ITEM_COMMAND:
      return receive_use_item(socket);
    default:
      return nullptr;
  }
}

void send_login(const Socket& socket, const LoginCommandDTO* login_command) {
  uint8_t command_id = LOGIN_COMMAND;
  uint8_t room_number = login_command->room_number;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&room_number, 1);
}

void send_quit(const Socket& socket, const QuitCommandDTO* quit_command) {
  uint8_t command_id = QUIT_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_move(const Socket& socket, const MoveCommandDTO* move_command) {
  uint8_t command_id = MOVE_COMMAND;
  uint8_t move_type = move_command->movement_type;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&move_type, 1);
}

void send_attack(const Socket& socket, const AttackCommandDTO* attack_command) {
  uint8_t command_id = ATTACK_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_pick_up_item(const Socket& socket,
                       const PickUpCommandDTO* pick_up_command) {
  uint8_t command_id = PICK_UP_ITEM_COMMAND;
  socket.send(&command_id, ID_LENGTH);
}

void send_use_item(const Socket& socket, const UseItemCommandDTO* use_command) {
  uint8_t command_id = USE_ITEM_COMMAND;
  uint8_t item = use_command->item;
  uint8_t item_slot = use_command->item_slot;
  uint8_t is_equipped = use_command->equipped;
  socket.send(&command_id, ID_LENGTH);
  socket.send(&item, ID_LENGTH);
  socket.send(&item_slot, ID_LENGTH);
  socket.send(&is_equipped, ID_LENGTH);
}

void Protocol::send_command(const Socket& socket, CommandDTO* commandDTO) {
  switch (commandDTO->get_id()) {
    case LOGIN_COMMAND:
      send_login(socket, static_cast<LoginCommandDTO*>(commandDTO));
      break;

    case QUIT_COMMAND:
      send_quit(socket, static_cast<QuitCommandDTO*>(commandDTO));
      break;

    case MOVE_COMMAND:
      send_move(socket, static_cast<MoveCommandDTO*>(commandDTO));
      break;

    case ATTACK_COMMAND:
      send_attack(socket, static_cast<AttackCommandDTO*>(commandDTO));
      break;
    case PICK_UP_ITEM_COMMAND:
      send_pick_up_item(socket, static_cast<PickUpCommandDTO*>(commandDTO));
      break;
    case USE_ITEM_COMMAND:
      send_use_item(socket, static_cast<UseItemCommandDTO*>(commandDTO));
      break;
    default:
      break;
  }
}

/********************** NOTIFICACIONES ***********************************/

void Protocol::send_notification(const Socket& socket, Notification* n) {
  std::vector<unsigned char> serialization = n->vector;
  uint16_t size = htons(serialization.size());
  socket.send(&size, 2);
  socket.send(serialization.data(), serialization.size());
}

// Definir que devuelve la clase (Puede moverse la notificacion que tengo en el
// server a protocol/common y usar eso)
void Protocol::receive_notification(const Socket& socket,
                                    std::vector<unsigned char>& vector) {
  uint16_t notification_size = 0;
  socket.recv(&notification_size, 2);
  notification_size = ntohs(notification_size);
  unsigned char* buffer = new unsigned char[notification_size];
  socket.recv(buffer, notification_size);
  vector = std::vector<unsigned char>(buffer, buffer + notification_size);
  delete buffer;
}