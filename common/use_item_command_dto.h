#ifndef USE_ITEM_COMMAND_DTO_H
#define USE_ITEM_COMMAND_DTO_H

#include "command_dto.h"

class UseItemCommandDTO : public CommandDTO {
 public:
  UseItemCommandDTO(const int);
  UseItemCommandDTO(const UseItemCommandDTO&) = delete;
  ~UseItemCommandDTO();
  int get_id();
  int item_slot;
};

#endif