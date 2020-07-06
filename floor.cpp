//Marcelo Morales
//lmoral10

//A Floor tile is one that any Entity can move onto (or be pushed onto)


#include "floor.h"

Floor::~Floor() {
}

// Check whether specified Entity is allowed to move from fromPos onto
// tilePos.  tilePos can be assumed to be Position of this Tile.
// fromPos is not necessarily the Entity's Position, because this
// member function could be called as part of pathfinding, where
// it is important to know where in the Maze the Entity can move,
// regardless of where it is currently located.
 MoveResult Floor :: checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const {

   // Unused variables.
   (void) entity;
   (void) fromPos;
   (void) tilePos;
   
   //able to move into a floor tile
   return MoveResult::ALLOW;
   
// Return true if this is the goal Tile, false if not.
 }
bool Floor :: isGoal() const {

    //floor is not a goal
    return false;    

}

// Get the glyph representing this Tile. Should be a single character.
std::string Floor :: getGlyph() const {

    //floor is represented by the "." character
    return ".";
}

