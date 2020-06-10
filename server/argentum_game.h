#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H
#include "../util/thread.h"
#include "map.h"
#include <vector>
#include <unistd.h>
class ArgentumGame : public Thread {
public:
    //Instancia una nueva sala de Argentum
    explicit ArgentumGame(const unsigned int room);
    ~ArgentumGame() override;
    void run() override;
    const unsigned int get_room();

private:
    unsigned int room = 0;
    bool alive = true;
    Map map;
    void update();
	void move_monsters();
	std::vector<BaseCharacter*> characters;
};

#endif //ARGENTUMGAME_H
