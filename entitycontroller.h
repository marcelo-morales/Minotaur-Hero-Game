#ifndef ENTITYCONTROLLER_H
#define ENTITYCONTROLLER_H

#include "position.h"


//A forward declaration is sufficient to allow pointers and references to the referred-to type 
//to be declared. However, actual uses of the type, such as instantiating an object or calling
// a member function, require the definition of the class to be known.
class Game;
class Entity;

class EntityController {
private:
  // copy constructor and assignment operator disallowed
  EntityController(const EntityController &);
  EntityController &operator=(const EntityController &);

public:
  EntityController();
  virtual ~EntityController();

  // Return a Direction specifying the direction in which
  // specified Entity should try to move.
  virtual Direction getMoveDirection(Game *game, Entity *entity) = 0;

  // Return true if this EntityController is controlled by
  // user input. EntityControllers other than UIControl should
  // return false.
  virtual bool isUser() const = 0;
};

#endif // ENTITYCONTROLLER_H
