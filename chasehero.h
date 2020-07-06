// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#ifndef CHASEHERO_H
#define CHASEHERO_H

#include "entitycontroller.h"
#include "game.h"
#include "entity.h"
#include <string>

class ChaseHero : public EntityController {
private:
  // disallow copy constructor and assignment operator
  ChaseHero(const ChaseHero &);
  ChaseHero &operator=(const ChaseHero &);

public:
  ChaseHero();
  virtual ~ChaseHero();

  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;

private:
  // Determines the closest hero to the controlled Entitty pointer.
  Entity * closestHero(std::vector<Entity *> heroes, Entity *entity);

  // Determines which of the 4 directions that the entity is able to move in.
  void checkDirections(Game *game, Entity *entity, Entity *hero, bool& right, bool& left, bool& up, bool& down);

  // Sets the string variables horizontal and vertical to left or right and up and down, respectively,
  // depending on the sign of the horizontal and vertical distances.
  void setStringDirections(std::string& horizontal, std::string& vertical, int posX, int posY, int heroX, int heroY);

  // Returns Direction::RIGHT or Direction::LEFT depending on what the string direction is.
  Direction leftOrRight(std::string direction);

  // This function has a preference for moving vertically, up or left.                                                                                                                                   
  // According to what moves are possible, this function returns the correct direction. Otherwise, returns                                                                                               
  // Direction::NONE. 
  Direction verticalDir(std::string preferred, bool preferredCheck, std::string alternate, bool alternateCheck);
  
  // This function has a preference of moving horizontally, right or left.
  // According to what moves are possible, this function returns the correct direction. Otherwise, returns
  // Direction::NONE.
  Direction horizontalDir(std::string preferred, bool preferredCheck, std::string alternate, bool alternateCheck);

  // Calls and returns the horizontalDir function. The parameters of the horizontalDir function
  // are dependent on what the string variable direction is.
  Direction horizontalCaller(std::string direction, bool upCheck, bool downCheck, std::string horizontal, bool horizontalCheck);

  // Calls and returns the verticalDir function. The parameters of the verticalDir function                                                                                                          
  // are dependent on what the string variable direction is.                                                                                                                                             
  Direction verticalCaller(std::string direction, bool rightCheck, bool leftCheck, std::string vertical, bool verticalCheck);
};

#endif // CHASEHERO_H
