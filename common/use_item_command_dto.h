#ifndef USE_ITEM_COMMAND_DTO_H
#define USE_ITEM_COMMAND_DTO_H

#include "command_dto.h"

class UseItemCommandDTO : public CommandDTO {
 public:
  UseItemCommandDTO(const int it, const int slot, const bool equip);
  UseItemCommandDTO(const UseItemCommandDTO&) = delete;
  ~UseItemCommandDTO();
  int get_id();
  int item;
  int item_slot;
  int equipped;
};

#endif
