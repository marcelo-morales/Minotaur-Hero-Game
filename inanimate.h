// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#ifndef INANIMATE_H
#define INANIMATE_H

#include "entitycontroller.h"

// EntityController for inanimate objects.
// Such objects never move on their own, so getMoveDirection should always
// return Direction::NONE.  Such objects *can* be pushed by other
// (animate) Entity objects.
class Inanimate : public EntityController {
private:
  // copy constructor and assignment operator are disallowed
  Inanimate(const Inanimate &);
  Inanimate &operator=(const Inanimate &);

public:
  Inanimate();
  virtual ~Inanimate();

  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;
};

#endif // INANIMATE_H
