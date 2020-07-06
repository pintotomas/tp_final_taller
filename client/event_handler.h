#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <SDL2/SDL.h>

#include <vector>

#include "attack_command_dto.h"
#include "character.h"
#include "commands_blocking_queue.h"
#include "events_queue.h"
#include "exception_messages.h"
#include "interactive_box.h"
#include "move_command_dto.h"
#include "npc.h"
#include "pick_up_command_dto.h"
#include "playable_character.h"
#include "quit_command_dto.h"
#include "sdl_exception.h"
#include "texture.h"
#include "use_item_command_dto.h"

class EventHandler {
 private:
  CommandsBlockingQueue& commands_queue;
  EventsQueue& events_queue;
  bool& is_running;
  SoundEffect background_music;
  InteractiveBox inventory;
  InteractiveBox text_box;

 public:
  EventHandler(CommandsBlockingQueue& commands_queue, EventsQueue&, bool&);
  ~EventHandler();
  bool is_up();
  void get_events();
};

#endif
