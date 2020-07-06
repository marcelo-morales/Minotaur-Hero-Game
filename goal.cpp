// Samuel Atefah; JHED: satefah1                                                                                                                                                                         
// Chiamaka Anaemeribe; JHED: canaeme1    
// Marcelo Morales; JHED: lmoral10  

#include "goal.h"

// A Goal is a tile that allows a Hero to win if they move upon it.                                                                                                                                                          
Goal::~Goal() {
}

MoveResult Goal::checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const {
  (void) entity; (void) fromPos; (void) tilePos;
  return MoveResult::ALLOW;
}

bool Goal::isGoal() const { return true; }

std::string Goal::getGlyph() const { return "<"; }
