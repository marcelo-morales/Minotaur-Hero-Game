// Samuel Atefah; JHED: satefah1
// Chiamaka Anaemeribe; JHED: canaeme1
// Marcelo Morales; JHED: lmoral10

#include "chasehero.h"
#include "game.h"
#include "entity.h"
#include <vector>
#include "position.h"
#include "basicgamerules.h"
#include <string>

using std::vector; using std::string;

ChaseHero::ChaseHero() : EntityController() {}

ChaseHero::~ChaseHero() {
}

// Determines the closest hero to the controlled Entitty pointer.                                                                                                                                       
Entity * ChaseHero::closestHero(std::vector<Entity *> heroes, Entity *entity) {

  Entity * closest = heroes.front();
  Position closestPos = closest->getPosition();
  Position entityPos = entity->getPosition();
  
  int leastDistance = entityPos.distanceFrom(closestPos);

  // Checks to see which is the closest hero
  for(vector<Entity *>::const_iterator it = heroes.cbegin();
      it != heroes.cend(); ++it) {

    Position heroPos = (*it)->getPosition();
    int distance = entityPos.distanceFrom(heroPos);

    if(distance < leastDistance) {
      leastDistance = distance;
      closest = *it;
    }
  }

  return closest;
}

// Determines which of the 4 directions that the entity is able to move in.                                                                                                                             
void ChaseHero::checkDirections(Game *game, Entity *entity, Entity *hero, bool& right, bool& left, bool& up, bool& down) {

  const Position entityPos = entity->getPosition();
  const Position heroPos = hero->getPosition();
  
  Position rightPos = entityPos.displace(Direction::RIGHT);
  Position leftPos = entityPos.displace(Direction::LEFT);
  Position upPos = entityPos.displace(Direction::UP);
  Position downPos = entityPos.displace(Direction::DOWN);

  int before_distance = entityPos.distanceFrom(heroPos);

  int right_distance = rightPos.distanceFrom(heroPos);
  int left_distance = leftPos.distanceFrom(heroPos);
  int up_distance = upPos.distanceFrom(heroPos);
  int down_distance = downPos.distanceFrom(heroPos);
  
  
  BasicGameRules * bg = new BasicGameRules();

  if(right_distance < before_distance && bg->allowMove(game, entity, entityPos, rightPos)) {
    right = true;
  }

  if(left_distance < before_distance && bg->allowMove(game, entity, entityPos, leftPos)) {
    left = true;
  }

  if(up_distance < before_distance && bg->allowMove(game, entity, entityPos, upPos)) {
    up = true;
  }

  if(down_distance < before_distance && bg->allowMove(game, entity, entityPos, downPos)) {
    down = true;
  }
  
  delete bg;
}

// Sets the string variables horizontal and vertical to left or right and up and down, respectively,                                                                                                    
// depending on the sign of the horizontal and vertical distances.                                                                                                                                    
void ChaseHero::setStringDirections(std::string& horizontal, std::string& vertical, int posX, int posY, int heroX, int heroY) {
  
  if(posX > heroX) {
    horizontal = "left";
  }
  else if(posX < heroX) {
    horizontal = "right";
  }
  
  if(heroY < posY) {
    vertical = "up";
  }
  else if(heroY > posY) {
    vertical = "down";
  }
}

// Returns Direction::RIGHT or Direction::LEFT depending on what the string variable direction is.                                                                                                     
Direction ChaseHero::leftOrRight(std::string direction) {

  if(direction == "left") {
    return Direction::LEFT;
  }

  return Direction::RIGHT;
}

// This function has a preference for moving vertically, up or left.                                                                                                                                   
// According to what moves are possible, this function returns the correct direction. Otherwise, returns Direction::NONE.                                                                                
Direction ChaseHero::verticalDir(std::string preferred, bool preferredCheck, std::string alternate, bool alternateCheck) {
 if(preferred == "up") {

   if(preferredCheck) { 
     return Direction::UP;
    }
   else if(alternateCheck) {
     return leftOrRight(alternate);
   }
 }
 else if(preferred == "down") {
   
   if(preferredCheck) {
     return Direction::DOWN;
   }
   else if(alternateCheck) {
     return leftOrRight(alternate);  
   }
 }
 
 return Direction::NONE;
}

// This function has a preference of moving horizontally, right or left.                                                                                                                                 
// According to what moves are possible, this function returns the correct direction. Otherwise, returns Direction::NONE.                                                                               
Direction ChaseHero::horizontalDir(std::string preferred, bool preferredCheck, std::string alternate, bool alternateCheck) {
  if(preferred == "right") {

    if(preferredCheck) {
      return Direction::RIGHT;
    }
    else if(alternateCheck) {
      return verticalDir(alternate, alternateCheck, preferred, preferredCheck);
    }
  }
  else if(preferred == "left") {

    if(preferredCheck) {
      return Direction::LEFT;
    }
    else if(alternateCheck) {
      return verticalDir(alternate, alternateCheck, preferred, preferredCheck);
    }
  }

  return Direction::NONE;
}

// Calls and returns the horizontalDir function. The parameters of the horizontalDir function                                                                                                           
// is dependent on what the string variable direction is.                                                                                                                                              
Direction ChaseHero::horizontalCaller(std::string direction, bool upCheck, bool downCheck, std::string horizontal, bool horizontalCheck) {

  if(direction == "up") {
    return horizontalDir(horizontal, horizontalCheck, direction, upCheck);
  }

  else if(direction == "down"){
    return horizontalDir(horizontal, horizontalCheck, direction, downCheck);
  }
  else if(direction == "" && horizontalCheck) {

    return horizontalDir(horizontal, horizontalCheck, direction, upCheck);
  }

  return Direction::NONE;
}

// Calls and returns the verticalDir function. The parameters of the verticalDir function                                                                                                               
// are dependent on what the string variable direction is.                                                                                                                                             
Direction ChaseHero::verticalCaller(std::string direction, bool rightCheck, bool leftCheck, std::string vertical, bool verticalCheck) {

  if(direction == "right") {
    return verticalDir(vertical, verticalCheck, direction, rightCheck);
  }
  else if(direction == "left") {
    return verticalDir(vertical, verticalCheck, direction, leftCheck);
  }
   else if(direction == "" && verticalCheck) {

    return verticalDir(vertical, verticalCheck, direction, rightCheck);
  }

  return Direction::NONE;
}

// Returns Direction that moves the controlled entity towards the closest
// Entity object with the "h" (Hero) property.
Direction ChaseHero::getMoveDirection(Game *game, Entity *entity) {

  vector<Entity *> heroes = game->getEntitiesWithProperty('h');

  if(heroes.empty()) {
    return Direction::NONE;
  }

  // Gets closest hero to entity.
  Entity * hero = this->closestHero(heroes, entity);

  bool right = false;
  bool left = false;
  bool up = false;
  bool down = false;

  // Checks which moves are possible.
  checkDirections(game, entity, hero, right, left, up, down);

  string horizontal = "";
  string vertical = "";
  
  int entityX = entity->getPosition().getX();
  int entityY = entity->getPosition().getY();
  
  int heroX = hero->getPosition().getX();
  int heroY = hero->getPosition().getY();
  
  int xDistance = entityX - heroX;
  if(xDistance < 0) {
    xDistance = -xDistance;
  }

  int yDistance = entityY - heroY;
  if(yDistance < 0) {
    yDistance = -yDistance;
  }
  // Determines which directions the entity should move.
  setStringDirections(horizontal, vertical, entityX, entityY, heroX, heroY);

  // Picks the appropriate direction.
  if(xDistance > yDistance) {
   if(horizontal == "right") {
     return horizontalCaller(vertical, up, down, horizontal, right);
   }
   else if(horizontal == "left") {
     return horizontalCaller(vertical, up, down, horizontal, left);
   }
 }
  else if(xDistance < yDistance) {
   if(vertical == "up") {
     return verticalCaller(horizontal, right, left, vertical, up);
   }
   else if(vertical == "down") {
     return verticalCaller(horizontal, right, left, vertical, down);
   }
 }
 else {
   if(horizontal == "right") {
     return horizontalCaller(vertical, up, down, horizontal, right);
   }
   else if(horizontal == "left") {
     return horizontalCaller(vertical, up, down, horizontal, left);
   }
 }

 return Direction::NONE;
}

// Returns false since it is not the user.
bool ChaseHero::isUser() const {
  return false;
}
