// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#include "inanimate.h"
#include "position.h"


Inanimate :: Inanimate() {

}

Inanimate :: ~Inanimate() {

}

//inanimate is not moving, so it's direction is none
Direction Inanimate :: getMoveDirection(Game *game, Entity *entity) {
    //return direction should be None
    (void) game;
    (void) entity;
    return Direction::NONE;
}

//return false because inanimate is never controlled by the user
bool Inanimate :: isUser() const {
    return false;
}
